#include "List.hpp"
#include <iostream>


int main ()
{
    List <int> exp;
    
    for (int i = 0; i < 10; ++i)
    {
        exp.pushFront(i);
    }  

    exp.removeByIndex(4);

    for (int i = 0; i < 9; ++i)
    {
        //std::cout<<exp.getValue(i)<<std::endl;
    } 

    std::cout<<exp.len()<<std::endl;

    return 0;
}



