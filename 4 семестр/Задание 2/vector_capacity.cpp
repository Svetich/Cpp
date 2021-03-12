#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main()
{
    default_random_engine gen; //генератор случайных чисел
    //равномерное распределение от 0 до 10.0
    uniform_real_distribution<double> dist(0.0,10.0);
    vector<double> v1;

    int previousCapasity = 1;

    for (int i = 0; i <= 30; i++)
    {
        v1.push_back(dist(gen));
        cout << "size1" << endl;
        cout << v1.size() << endl;
        cout << "capacity1" << endl;
        cout << v1.capacity() << endl;
        
        if (v1.capacity() > previousCapasity)
        {
            cout << "capacity1 rised" << endl;
            cout << v1.capacity() / previousCapasity << endl;
        }       
        previousCapasity = v1.capacity();
    }

    /*каждый раз, когда ёмкости не хватает (т.е. размер превышает ёмкость), 
    она увеличивается в 2 раза (2, 4, 8, 16, 32 и т.д.)*/

    vector<int> v2;
    v2.reserve(32);

    previousCapasity = 1;

    for (int i = 0; i <= 40; i++)
    {
        v2.push_back(dist(gen));
        cout << "size2" << endl;
        cout << v2.size() << endl;
        cout << "capacity2" << endl;
        cout << v2.capacity() << endl;
        
        if (v2.capacity() > previousCapasity)
        {
            cout << "capacity2 rised" << endl;
            cout << v2.capacity() / previousCapasity << endl;
        }       
        previousCapasity = v1.capacity();
    }

    /*если установлена начальная ёмкость, то она не меняется до того как размер не будет больше,
    чем ёмкость (если это случится, то он увеличится в 2 раза) */
    
    return 0;
}
