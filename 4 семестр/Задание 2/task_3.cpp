#include <iostream>
#include <array>

using namespace std;

int main()
{
    array <int, 5> height = {3, 0, 2, 0, 4};
    int length = 5;

    int index_0 = 0;
    int index_n = length;

    int value_0 = 0;
    int value_n = 0;
    
    int volume = 0;
       
    while(index_0 < index_n)
    {
        if(height[index_0] > value_0)
        {
            value_0 = height[index_0];
        }
        if(height[index_n] > value_n)
        {
            value_n = height[index_n];
        }
        if(value_0 >= value_n)
        {
            volume += value_n - height[index_n];
            index_n--;
        }
        else
        {
            volume += value_0 - height[index_0];
            index_0++;
        }
    }
    cout << volume << endl;
        
return 0;
}