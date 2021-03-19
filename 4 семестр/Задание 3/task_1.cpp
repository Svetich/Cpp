#include <iostream>
#include <cstdlib> 
#include <set>
#include <array>
#include <algorithm>
#include <chrono>


using namespace std;
using namespace chrono;

int main()
{
    srand(20);

    int N = 30;

    array <int, 30> all_numbers;   

    for (int i = 0; i <= all_numbers.size(); i++)
    {
        all_numbers[i] = rand();
    }

    auto start = high_resolution_clock::now();
    
    set <int, greater<int>> cont1;

    for (int i = 0; i <= all_numbers.size(); i++)
        {
            cont1.insert(all_numbers[i]);
        }
    
    auto one = high_resolution_clock::now();

    array <int, 30> cont2;

    for (int i = 0; i <= all_numbers.size(); i++)
        {
            cont2[all_numbers[i]];
        }

    sort(cont2.begin(), cont2.end());

    auto two = high_resolution_clock::now();

    duration<double> time_array = duration_cast<duration<double>>(one - start);
    duration<double> time_set = duration_cast<duration<double>>(two - one);

    cout << "array" << endl;
    cout << time_array.count() << endl;
    cout << "set" << endl;
    cout << time_set.count() << endl;

    //set заполняется быстрее

    return 0;
}