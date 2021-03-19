#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    // множество без повторяющихся элементов, в котором элементы сортируются по убыванию
    set<int,greater<int>> coll1;
    // вставка элементов
    coll1.insert({4,3,5,1,6,2});
    coll1.insert(5);
    // вывод элементов на экран
    for (int elem : coll1) {
        cout << elem << ' ';
    }
    cout << endl;
    // вставляем 4, если status.first == True, т.е. успешно вставили элемент
    // то вычисляем расстояние от начала множества до позиции, где был вставлен элемент
    auto status = coll1.insert(4);
    if (status.second) {
        cout << "4 inserted as element "
             << distance(coll1.begin(),status.first) + 1 << endl;
    } // если status.first == False, значит, элемент уже есть в множестве
    else {
        cout << "4 already exists" << endl;
    }
    // создаем новое множество coll2 с элементами множества coll1 в обратном порядке
    set<int> coll2(coll1.cbegin(),coll1.cend());
    // выводим на экран элементы с использованием потоковых итераторов
    copy(coll2.cbegin(), coll2.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;
    // удаление элементов, равных 3
    coll2.erase(coll2.begin(), coll2.find(3));
    // удаление элементов, равных 5
    int num;
    num = coll2.erase (5); // num - сколько элементов удалили
    cout << num << " element(s) removed" << endl;
    copy (coll2.cbegin(), coll2.cend(),
          ostream_iterator<int>(cout," "));
    cout << endl;
}

