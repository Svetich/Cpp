#include <iostream>

using namespace boost;
using namespace std;

struct phone {
    string name;
    string number;
};

typedef multi_index_container<
    phone,
    indexed_by<
    ordered_non_unique<
    member<phone, string, &phone::name>
    >,
    random_access<>,
    hashed_non_unique<
    member<phone, string, &phone::name>
    >
    >
> phone_multi;

int main()
{
    phone_multi phonebook;
    phonebook.push_back("Kate", "8(901)3355787");
    phonebook.push_back("Ann", "8(903)9565871");
    phonebook.push_back("Victor", "8(921)7752758");

    auto& ordered_index = animals.get<0>;
    auto& access_index = animals.get<1>;
    auto& hashed_index = animals.get<2>;

    for (auto i : ordered_index) {
        cout << i.name << ' ' << i.phone << endl;
    }

    cout << access_index[1].name << ' ' << access_index[1].phone << endl;
    cout << access_index[2].name << ' ' << access_index[2].phone << endl;
    cout << access_index[0].name << ' ' << access_index[0].phone << endl;

    cout << access_index["Kate"].phone << endl;
    cout << access_index["Ann"].phone << endl;
    cout << access_index["Victor"].phone << endl;
    return 0;
}