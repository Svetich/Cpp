#include <string>
#include <regex>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string data = "<person>\n"
                  " <first>Nico</first>\n"
                  " <last>Josuttis</last>\n"
                  "</person>\n";
    regex reg("<(.*)>(.*)</(\\1)>");
    // перебираем все соответствия с помощью итератора
    sregex_token_iterator pos(data.begin(),data.end(),   // диапазон поиска
                              reg,                       // регулярное выражение для поиска
                              {0,2});      // 0: полное соответствие, 2: вторая подстрока
    sregex_token_iterator end;
    for ( ; pos!=end ; ++pos ) {
        cout << "match: " << pos->str() << endl;
    }
    /* Вывод: match: <first>Nico</first>
              match: Nico
              match: <last>Josuttis<last>
              match: Josuttis */
}

