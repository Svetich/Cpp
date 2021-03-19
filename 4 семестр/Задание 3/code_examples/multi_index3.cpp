#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>

using namespace boost::multi_index;

struct animal
{
  std::string name;
  int legs;
};

typedef multi_index_container<
  animal,
  indexed_by<
    sequenced<>, /* последовательность, в которой элементы упорядочены
                    в порядке добавления */
    ordered_non_unique<
      member<
        animal, int, &animal::legs // поиск по полю legs структуры animal
      >
    >,
    random_access<> // можно обращаться по индексу к элементу контейнера
  >
> animal_multi;

int main()
{
  animal_multi animals;

  // добавление элементов
  animals.push_back({"cat", 4});
  animals.push_back({"shark", 0});
  animals.push_back({"spider", 8});

  // объект для поиска элементов в  контейнере по полю legs
  auto &legs_index = animals.get<1>();
  for(auto it = legs_index.begin(); it != legs_index.end(); it++)
    std::cout << it->name << ' ' << it->legs << std::endl;
  std::cout << std::endl;

  // объект, чтобы обращаться к элементам контейнера по индексу
  const auto &rand_index = animals.get<2>();
  std::cout << rand_index[0].name << '\n';
}



