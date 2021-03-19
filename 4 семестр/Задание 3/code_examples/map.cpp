#include <map>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    typedef map<string,float> StringFloatMap;
    // отображение, ключи - типа string, значения - типа float
    StringFloatMap stocks;
    // вставка элементов
    stocks["BASF"] = 369.50;
    stocks["VW"] = 413.50;
    stocks["Daimler"] = 819.00;
    stocks["BMW"] = 834.00;
    stocks["Siemens"] = 842.20;
    // вывод элементов на экран
    StringFloatMap::iterator pos;
    cout << left;  // задаем выравнивание
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        cout << "stock: " << setw(12) << pos->first
             << "price: " << pos->second << endl;
    }
    cout << endl;
    // удвоение в цикле всех значений отображения
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        pos->second *= 2;
    }
    cout << endl;
    /* переименование ключа "VW" в "Volkswagen"
       для этого добавляем элемент с ключом "Volkswagen" и значением, равным
       значению по ключу "VW", а старый элемент удаляем */
    stocks["Volkswagen"] = stocks["VW"];
    stocks.erase("VW");
}

