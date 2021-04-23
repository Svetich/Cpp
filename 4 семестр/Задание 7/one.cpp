#include <iostream>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>
#include <execution>
#include <vector>
#include <functional>

using namespace std;


void Pi_search(int N, int Radius)
{
    int N_in = 0;

    random_device random_device; 
    mt19937 generator(random_device());

    uniform_int_distribution<> distribution(-Radius, Radius); 

    for (int i = 0; i < 2 * N; i++)
    {
        int x = distribution(generator);
        int y = distribution(generator);
        if ((x * x + y * y) <= Radius * Radius)
        {
            N_in++;
        }
    }
    cout << 4 * double(N_in) / double(N) << endl; 
}

int main(int argc, char ** argv)
{
    int N = 1000000;
    int n = thread::hardware_concurrency();
    int Radius = 1;

    vector<thread> threads;

    int each = N/n;

    for (size_t i = 0 ; i < n; i++)
    {
        threads.push_back(thread(Pi_search, each, Radius));
    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
}