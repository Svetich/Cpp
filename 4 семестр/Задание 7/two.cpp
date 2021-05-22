#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

template<typename Iterator, typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result);
	}
};


template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, unsigned long const threads)
{
	unsigned long const len = std::distance(first, last);

	if (!len)
		return init;

	unsigned long const size = len / threads;
	std::vector<T> results(threads);
	std::vector<std::thread> threads(threads - 1);
	Iterator start = first;
	
	for (unsigned long i = 0; i < (threads - 1); ++i)
	{
		Iterator end = start;
		std::advance(end, size);
		threads[i] = std::thread(accumulate_block<Iterator, T>(), start, end, std::ref(results[i]));
		start = end;
	}

	accumulate_block<Iterator, T>() (start, last, results[threads - 1]);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
};



int main(void)
{
	vector < int > vec(100);
	iota(vec.begin(), vec.end(), 1);

	float x;

	HDC hdc = GetDC(GetConsoleWindow());
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, pen);
	MoveToEx(hdc, 10, 0, NULL);
	LineTo(hdc, 10, 260);
	MoveToEx(hdc, 0, 250, NULL);
	LineTo(hdc, 200, 250);

	auto start = high_resolution_clock::now();
	parallel_accumulate(vec.begin(), vec.end(), 0, 1);

	auto end = high_resolution_clock::now();
	auto oldtime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	for (unsigned long i = 2; i < 15; i++)
	{
		auto start = high_resolution_clock::now();
		parallel_accumulate(vec.begin(), vec.end(), 0, i);
		auto end = high_resolution_clock::now();
		auto elapsed_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		MoveToEx(hdc, 10 * (i - 1) + 10, -0.2 * oldtime.count() + 250, NULL);
		LineTo(hdc, 10 * i + 10, -0.2 * elapsed_ns.count() + 250);
		oldtime = elapsed_ns;
	}

	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();

	return 0;
}
