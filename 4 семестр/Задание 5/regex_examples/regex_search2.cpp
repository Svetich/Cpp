#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string data = "<person>\n"
                  " <first>Ivan</first>\n"
                  " <last>Josuttis</last>\n"
                  "</person>\n";
    regex reg("<(.*)>(.*)</(\\1)>");
    sregex_iterator pos(data.cbegin(), data.cend(), reg);
    sregex_iterator end;
    for ( ; pos!=end; ++pos)
    {
        cout << pos->str() << '\t' << pos->str(1) << '\t' << pos->str(2) << '\t' << pos->str(3) << endl;
    }
    /*  выведет:
        <first>Ivan</first> first   Ivan    first
        <last>Josuttis</last>   last    Josuttis    last */

    return 0;
}

