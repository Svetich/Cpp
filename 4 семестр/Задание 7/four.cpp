#include <iostream>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>
#include <execution>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    vector<int> vec = {1, 5, 3, 7, 9, 1};
    vector<int>::iterator it;

    auto start = chrono::high_resolution_clock::now();
    sort(execution::par, vec.begin(), vec.end());
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto rng = default_random_engine {};
    shuffle(begin(vec), end(vec), rng);

    auto start = chrono::high_resolution_clock::now();
    sort(execution::seq, vec.begin(), vec.end());
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto rng = default_random_engine {};
    shuffle(begin(vec), end(vec), rng);
//finding
    auto start = chrono::high_resolution_clock::now();
    it = find(execution::par, vec.begin(), vec.end(), 5);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto start = chrono::high_resolution_clock::now();
    it = find(execution::seq, vec.begin(), vec.end(), 5);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;

//counting
    auto start = chrono::high_resolution_clock::now();
    it = count(execution::par, vec.begin(), vec.end(), 1);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto start = chrono::high_resolution_clock::now();
    it = count(execution::seq, vec.begin(), vec.end(), 1);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;
}
  