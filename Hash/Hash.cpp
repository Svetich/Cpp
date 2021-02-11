#pragma once
#include <list>
#include <vector>
#include <fstream>
#include <string>


class hashFunctions
{
    public:
        std::string str;

    hashFunctions()
    {

    }

    hashFunctions(std::string str)
    {
        this->str = str;
    }

    int hashFunction1()
    {
        int hash = str.size();
        return hash;
    }

    int hashFunction2()
    {
        int hash = str[0];
        return hash;
    }
};