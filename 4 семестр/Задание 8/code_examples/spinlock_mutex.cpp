#include <atomic>

class spinlock_mutex
{
public:

	spinlock_mutex() :
		m_flag(ATOMIC_FLAG_INIT)
	{}

public:

	void lock()
	{
		while (m_flag.test_and_set(std::memory_order_acquire));
	}

	void unlock()
	{
		m_flag.clear(std::memory_order_release);
	}

private:

	std::atomic_flag m_flag;
};

int main(int argc, char ** argv)
{
	system("pause");

	return EXIT_SUCCESS;
}
