#include <boost/multi_array.hpp>
#include <iostream>

using namespace std;

int main()
{
  int arr[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  // инициализация двумерного массива обычным массивом
  boost::multi_array_ref<int, 2> a{arr, boost::extents[2][6]};

}

