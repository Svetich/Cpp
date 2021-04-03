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
    cout << regex_replace(data,                   // данные
                          reg,                    // регулярное выражение
                          "<$1 value=\"$2\"/>");  // замена

    /* Вывод: <person>
               <first value="Nico"/>
               <last value="Josuttis"/>
              <person> */
}
