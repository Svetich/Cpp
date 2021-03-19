#include <unordered_set>
#include <numeric> // для функции accumulate
#include <iostream>
#include <string>

template <typename T>
inline void PRINT_ELEMENTS (const T& coll,
                            const std::string& optstr="")
{
    std::cout << optstr;
    for (const auto&  elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    // создание и инициализация неупорядоченного множества
    unordered_set<int> coll = { 1,2,3,5,7,11,13,17,19,77 };
    PRINT_ELEMENTS(coll);
    /* вставка элементов. Может вызвать рехэширование и элементы
       могут переместиться в другом порядке */
    coll.insert({-7,17,33,-11,17,19,1,13});
    PRINT_ELEMENTS(coll);
    coll.erase(33); // удаление элемента

    // вставка суммы всех элементов
    coll.insert(accumulate(coll.begin(),coll.end(),0));
    PRINT_ELEMENTS(coll);
    // проверка, есть ли элемент 19 в  контейнере
    if (coll.find(19) != coll.end()) {
        cout << "19 is available" << endl;
    }
    // удаление всех отрицательных значений
    unordered_set<int>::iterator pos;
    for (pos=coll.begin(); pos!= coll.end(); ) {
        if (*pos < 0) {
            pos = coll.erase(pos);
        }
        else {
            ++pos;
        }
    }
    PRINT_ELEMENTS(coll);
}
