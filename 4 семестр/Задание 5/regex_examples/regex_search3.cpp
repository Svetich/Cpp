#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

int main()
{
    string data = "<person>\n"
                  " <first>Ivan</first>\n"
                  " <last>Josuttis</last>\n"
                  "</person>\n";
    regex reg("<(.*)>(.*)</(\\1)>");
    sregex_iterator beg(data.cbegin(), data.cend(), reg);
    sregex_iterator end;
    for_each(beg, end, [](const smatch &m)
    {
        cout << m.str() << '\t' << m.str(1) << '\t' << m.str(2) << '\t' << m.str(3) << endl;
    });
    /*  выведет:
        <first>Ivan</first> first   Ivan    first
        <last>Josuttis</last>   last    Josuttis    last */

    return 0;
}

