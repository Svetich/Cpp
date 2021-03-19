#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost::multi_index;

// структура, содержащая два элемента: название животного и количествоо его ног
struct animal
{
  string name;
  int legs;
};

// будем использовать multi_index_container
typedef multi_index_container<
  animal,           // структура, поля которой будут использоваться как ключи для поиска
  indexed_by<
    hashed_non_unique< // поле animal::name будет хешироваться
      member<
        animal, string, &animal::name
      >
    >,
    hashed_non_unique< // поле animal::legs также будет ключом для поиска и оно хешируется
      member<
        animal, int, &animal::legs
      >
    >
  >
> animal_multi;

int main()
{
  // создаем multi_index_container
  animal_multi animals;

  // вставка элементов в контейнер
  animals.insert({"cat", 4});
  animals.insert({"shark", 0});
  animals.insert({"spider", 8});

  /* создаем объект legs_index для поиска в контейнере
     по 2-му полю структуры, т.е. legs */
  auto &legs_index = animals.get<1>();
  // поиск элемента, где legs = 4
  // это элемент ("cat", 4)
  auto it = legs_index.find(4);
  // вывод на экран соотв. полей найденной структуры
  cout << it->name << ' ' << it->legs << endl;
  // изменение поля name в найденной структуре
  legs_index.modify(it, [](animal &a){ a.name = "dog"; });

  cout << animals.count("dog") << '\n';
}

