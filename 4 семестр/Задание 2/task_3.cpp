#include <stack>
#include <iostream>
#include <array>

using namespace std;

int main()
{
    stack<int> index;
    array<int, 5> height = {3, 0, 2, 0, 4};
    array<int, 5> length = {1, 0, 1, 0, 1};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

    for (int i = 0; i <= height.size(); i++)
    {
        index.push(i);
        cout << index.top() << endl;
    }

    for (int i = 0; i <= height.size(); i++)
    {
        if (index.empty() == false && height[i] > index.top())
        {
            index.push(i);
            index.pop();
            int dist 
        }
    }
return 0;
}                    


