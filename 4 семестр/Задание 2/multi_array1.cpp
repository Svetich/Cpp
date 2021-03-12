#include <boost/multi_array.hpp>
#include <iostream>

int main()
{
  // создание одномерного массива из 6 элементов
  boost::multi_array<char, 1> a{boost::extents[6]};

  a[0] = 'B';
  a[1] = 'o';
  a[2] = 'o';
  a[3] = 's';
  a[4] = 't';
  a[5] = '\0';

  // вывод массива на экран
  std::cout << a.origin() << '\n';
}
