#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace chrono;

// шаблон функции для измерения времени сортировки контейнера
template<typename T>
auto measureSortingTime(T container)
{
    auto start = high_resolution_clock::now();
    sort(container.begin(), container.end());
    auto end = high_resolution_clock::now();
    return end - start;
    //TODO: отсортировать контейнер (чтобы работало для vector, array и deque)
    //TODO: вычислить время сортировки и вернуть
}

// специализация шаблона для list
template<>
auto measureSortingTime(list<int> container)
{
    auto start = high_resolution_clock::now();
    container.sort();
    auto end = high_resolution_clock::now();
    return end - start;   
    //TODO: отсортировать list
    //TODO: вычислить время сортивки и вернуть
}


int main()
{
    default_random_engine generator; //генератор случайных чисел
    uniform_int_distribution<int> distribution(0,10000); //равномерное распределение от 0 до 1000
    auto gen = [&distribution, &generator](){
                   return distribution(generator); // лямбда-функция, которая генерирует случайное число
               };

    //можно поэспериментировать с разными размерами контейнеров
    vector<int> v(100000);
    // заполнение вектора случайными числами
    generate(v.begin(), v.end(), gen);
    array<int, 100000> a;
    deque<int> d(100000);
    list<int> l(100000);
    // нам нужно, чтобы все контейнеры были запонены одинаковыми даннными
    // поэтому скопируем данные из вектора в другие контейнеры
    copy (v.begin(), v.end(), a.begin()); //копирование элементов вектора v в массив a
    copy (v.begin(), v.end(), d.begin());
    copy (v.begin(), v.end(), l.begin());
    //sort(v.begin(), v.end()); // сортировка у vector, array и deque
    //l.sort() // сортировка у list
    
    auto vectorTime = measureSortingTime(v);
    duration<double> time_span_vector = duration_cast<duration<double>>(vectorTime);

    auto arrayTime = measureSortingTime(a);
    duration<double> time_span_array = duration_cast<duration<double>>(arrayTime);

    auto dequeTime = measureSortingTime(d);
    duration<double> time_span_deque = duration_cast<duration<double>>(dequeTime);

    auto listTime = measureSortingTime(l);
    duration<double> time_span_list = duration_cast<duration<double>>(listTime);

    cout << time_span_vector.count() << endl;
    cout << time_span_array.count() << endl;
    cout << time_span_deque.count() << endl;
    cout << time_span_list.count() << endl;


    /* быстрее всего сортируется array */

    return 0;
}
