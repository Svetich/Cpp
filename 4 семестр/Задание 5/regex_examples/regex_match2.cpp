#include <iostream>
#include <regex>

using namespace std;

int main()
{
    cout << boolalpha;

    regex reg1("<(.*)>.*</\\1>");
    bool found = regex_match("<tag>value</tag>", reg1); // true
    cout << found;

    return 0;
}

