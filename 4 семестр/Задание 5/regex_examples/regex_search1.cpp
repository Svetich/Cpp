#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string data = "XML tag: <tag-name>the value</tag-name>.";
    smatch m; // для возвращаемой информации о соответствии
    bool found = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));
    cout << boolalpha;
    cout << m.empty() << endl; // false
    cout << m.size() << endl; /* 4, так как в регулярном выражении три группы захвата,
    определенные в m[1], m[2] и m[3].
    В m[0] содержится вся подстрока <tag-name>the value</tag-name> соответствующая
    регулярному выражению. */
    cout << m.str() << endl; // выведет строку data
    cout << m.length() << endl; // 30 - длина <tag-name>the value</tag-name>
    cout << m.position() << endl; // 9 - позиция подстроки <tag-name>the value</tag-name>
    // в строке XML tag: <tag-name>the value</tag-name>.
    cout << m.prefix().str() << endl; // XML tag: - подстрока перед строкой, соотв. рег. выр.
    cout << m.suffix().str() << endl; // . подстрока после строки, соотв. рег. выр
    for (int i = 0; i<m.size(); i++)
        cout << m[i].str() << '\t' << m.position(i) << endl;
    /*  выведет:
        <tag-name>the value</tag-name>  9
        tag-name    10
        the value   19
        tag-name    30    */
    return 0;
}

