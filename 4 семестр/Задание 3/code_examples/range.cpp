#include <iostream>
#include <set>
using namespace std;

int main ()
{
    set<int> c;

    c.insert(1);
    c.insert(2);
    c.insert(4);
    c.insert(5);
    c.insert(6);

    cout << "lower_bound(3): " << *c.lower_bound(3) << endl; // выведет 4
    cout << "upper_bound(3): " << *c.upper_bound(3) << endl; // выведет 4
    cout << "equal_range(3): " << *c.equal_range(3).first << " "
                               << *c.equal_range(3).second << endl; // выведет 4 4
    cout << endl;
    cout << "lower_bound(5): " << *c.lower_bound(5) << endl; // выведет 5
    cout << "upper_bound(5): " << *c.upper_bound(5) << endl; // выведет 6
    cout << "equal_range(5): " << *c.equal_range(5).first << " "
                               << *c.equal_range(5).second << endl; // выведет 5 6
}

