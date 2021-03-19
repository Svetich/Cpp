#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>

using namespace boost::multi_index;

// структура, содержащая два элемента: название животного и количествоо его ног
struct animal
{
  std::string name;
  int legs;
};

// будем использовать multi_index_container
typedef multi_index_container<
  animal,           // структура, поля которой будут использоваться как ключи для поиска
  indexed_by<
    hashed_non_unique< // поле animal::name будет хешироваться
      member<
        animal, std::string, &animal::name
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

  // подсчет количества элементов с данным значением одного из ключей
  std::cout << animals.count("cat") << '\n';

  // создаем объект legs_index для поиска в контейнере по 2-му полю структуры, т.е. legs
  const animal_multi::nth_index<1>::type &legs_index = animals.get<1>();
  // подсчет количества элементов, где legs = 8
  std::cout << legs_index.count(8) << '\n';
}

