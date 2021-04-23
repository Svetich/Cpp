#include <iostream>
#include <string>
#include <regex>
#include <memory>
#include <atomic>
#include <thread>
#include <chrono>
#include <stack>
#include <mutex>
#include <random>
#include <vector>
#include <algorithm>

class Timer
{
public:

	Timer() : 
		tp(std::chrono::steady_clock::now())
	{}

	~Timer()
	{
		std::cout << "Time: " <<
			std::chrono::microseconds(
				std::chrono::duration_cast < std::chrono::microseconds > (
					std::chrono::steady_clock::now() - tp)).count() << " microseconds." << std::endl;
	}

private:

	std::chrono::steady_clock::time_point tp;
};

template < typename T >
class threadsafe_stack
{
private:

	std::stack < T > data;
	mutable std::mutex mutex;

public:

	threadsafe_stack() 
	{}

	threadsafe_stack(const threadsafe_stack & other)
	{
		std::lock_guard < std::mutex > lock(other.mutex);
		data = other.data;
	}

	threadsafe_stack & operator=(const threadsafe_stack &) = delete;

	void push(T new_value)
	{
		std::lock_guard < std::mutex > lock(mutex);
		data.push(new_value);
	}

	std::shared_ptr < T > pop()
	{
		std::lock_guard < std::mutex > lock(mutex);
		// if (data.empty()) { /**/ };
		const std::shared_ptr < T > result(std::make_shared < T > (data.top()));
		data.pop();
		return result;
	}

	void pop(T & value)
	{
		std::lock_guard < std::mutex > lock(mutex);
		// if (data.empty()) { /**/ };
		value = data.top();
		data.pop();
	}
};

template < typename T >
class lock_free_stack
{
private:

	struct node
	{
		std::shared_ptr < T > data;
		node * next;
		node(T const & d) :
			data(std::make_shared < T > (d))
		{}
	};

	std::atomic < node * > head;

	std::atomic < node * > nodes_to_be_deleted;

	std::atomic < std::size_t > threads_in_pop_counter;

private:

	static void delete_nodes(node * nodes)
	{
		while (nodes)
		{
			node * next = nodes->next;
			delete nodes;
			nodes = next;
		}
	}

	void try_delete_nodes(node * old_head)
	{
		if (threads_in_pop_counter.load(std::memory_order_relaxed) == 1)
		{
			node * nodes_to_delete = nodes_to_be_deleted.exchange(nullptr);

			if (!(threads_in_pop_counter.fetch_sub(1, std::memory_order_relaxed) - 1))
			{
				delete_nodes(nodes_to_delete);
			}
			else if (nodes_to_delete)
			{
				add_waiting_nodes(nodes_to_delete);
			}
			delete old_head;
		}
		else
		{
			add_waiting_node(old_head);
			threads_in_pop_counter.fetch_sub(1, std::memory_order_relaxed);
		}
	}

	void add_waiting_nodes(node * nodes)
	{
		node * last = nodes;
		while (node * const next = last->next)
		{
			last = next;
		}
		add_waiting_nodes(nodes, last);
	}

	void add_waiting_nodes(node * first, node * last)
	{
		last->next = nodes_to_be_deleted.load();
		while (!nodes_to_be_deleted.compare_exchange_weak(last->next, first));
	}

	void add_waiting_node(node* n)
	{
		add_waiting_nodes(n, n);
	}

public:

	void push(T const & data)
	{
		node * const new_node = new node(data);
		new_node->next = head.load(std::memory_order_relaxed);
		while (!head.compare_exchange_weak(new_node->next, new_node, std::memory_order_release, std::memory_order_relaxed));
	}

	//void pop(T & result)
	//{
	//	node * old_head = head.load();
	//	while (!head.compare_exchange_weak(old_head, old_head->next)); // !
	//	result = old_head->data; // !
	//}

	//std::shared_ptr < T > pop()
	//{
	//	node * old_head = head.load();
	//	while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
	//	return old_head ? old_head->data : std::shared_ptr < T >();
	//}

	std::shared_ptr < T > pop()
	{
		threads_in_pop_counter.fetch_add(1, std::memory_order_relaxed);

		node * old_head = head.load(std::memory_order_relaxed);
		while (old_head && !head.compare_exchange_weak(old_head, old_head->next, std::memory_order_acquire, std::memory_order_relaxed));

		std::shared_ptr < T > result;
		if (old_head)
		{
			result.swap(old_head->data); // move
			try_delete_nodes(old_head);
		}

		return result;
	}
};

// =============================================================================

std::atomic < bool > flag(false);

//using stack_t = threadsafe_stack < int >;
using stack_t = lock_free_stack  < int >;

stack_t s;

std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution <> uid(0, 100);

// =============================================================================

void push(const std::size_t size)
{
	while (!flag.load())
	{
		std::this_thread::yield();
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		// s.push(uid(generator));
		s.push(0);
	}
}

// =============================================================================

void pop(const std::size_t size)
{
	while (!flag.load())
	{
		std::this_thread::yield();
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		s.pop();
	}
}

// =============================================================================

int main()
{
	const std::size_t size = 1000U;
	const std::size_t number_of_threads = std::thread::hardware_concurrency();

	if (number_of_threads % 2 != 0 || number_of_threads == 0)
	{
		std::cerr << "Not acceptable number of threads: " << number_of_threads << ".\n";
		return EXIT_FAILURE;
	}

	const std::size_t initial_stack_size = size * number_of_threads / 2;

	for (std::size_t i = 0; i < initial_stack_size; ++i)
	{
		s.push(uid(generator));
	}

	std::vector < std::thread > push_threads(number_of_threads / 2);
	std::vector < std::thread > pop_threads (number_of_threads / 2);

	for (std::size_t i = 0; i < number_of_threads / 2; ++i)
	{
		push_threads[i] = std::thread(push, size);
		pop_threads [i] = std::thread(pop,  size);
	}

	{
		Timer t;

		flag.store(true);

		std::for_each(push_threads.begin(), push_threads.end(), std::mem_fn(&std::thread::join));
		std::for_each(pop_threads.begin(),  pop_threads.end(),  std::mem_fn(&std::thread::join));
	}

	system("pause");
}
