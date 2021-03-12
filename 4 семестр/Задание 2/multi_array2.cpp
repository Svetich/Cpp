#include <boost/multi_array.hpp>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  // двумерный массив
  boost::multi_array<int, 2> a{boost::extents[2][6]};
  /* Инициализация массива 0 1 2 3  4  5
                           6 7 8 9 10 11 */
  int cnt = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      a[i][j] = cnt;
      cnt++;
    }
  }
  // одномерный подмассив, полученный из двумерного
  typedef boost::multi_array<int, 2>::array_view<1>::type array_view;
  typedef boost::multi_array_types::index_range range;
  array_view view = a[boost::indices[0][range{0, 5}]]; // получим массив 0 1 2 3 4
  for (auto elem: view)
    cout << elem << ' ';
  cout << endl;

  reverse(view.begin(), view.end()); // получаем массив в обратном порядке 4 3 2 1 0

  for (auto elem: view)
    cout << elem << ' ';
  cout << endl;

  boost::multi_array<int, 2>::reference subarray = a[1]; // получим массив 6 7 8 9 10 11

  for (auto elem: subarray)
    cout << elem << ' ';
  cout << endl;
}
