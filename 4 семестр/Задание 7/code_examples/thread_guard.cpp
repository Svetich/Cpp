#include <thread>

class Thread_Guard
{
public:

	explicit Thread_Guard(std::thread & thread) noexcept :
		m_thread(thread)
	{}

	Thread_Guard			(const Thread_Guard &) = delete;

	Thread_Guard & operator=(const Thread_Guard &) = delete;

	~Thread_Guard() noexcept
	{
		try
		{
			if (m_thread.joinable())
			{
				m_thread.join();
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::thread & m_thread;
};

class F
{
public:

	explicit F(int & variable) noexcept:
		m_variable(variable) 
	{}

	void operator()() const noexcept
	{
		for (std::size_t i = 0; i < 1000000; ++i)
		{
			++m_variable;
		}
	}

	~F() noexcept = default;

private:

	int & m_variable;
};

int main(int argc, char ** argv)
{
	int local_variable = 42;

	F f(local_variable);

	std::thread thread(f);
	Thread_Guard guard(thread);

	// join -> OK

	// detach -> OK, but very dangerous

	// exception -> OK

	system("pause");

	return EXIT_SUCCESS;
}