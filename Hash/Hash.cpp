#pragma once
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <cmath>


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
        int numChar = str.size();
        int hash = 0;
        for(int i = 0; i < numChar; i++)
        {
            hash += str[i]; 
        }

        return hash;
    }

    int hashFunction3()
    {
        int numChar = str.size();
        int hash = 0;
        for(int i = 0; i < numChar; i++)
        {
            hash += str[i] + str[0]; 
        }

        return hash;
    }

    int hashFunction4()
    {
        int numChar = str.size();
        int hash = 0;
        for(int i = 0; i < numChar; i++)
        {
            hash += str[i] + str[numChar - 1]; 
        }

        return hash;
    }

    int hashFunction5()
    {
        int numChar = str.size();
        int hash = 0;
        for(int i = 0; i < numChar; i++)
        {
            hash += str[i] + pow(i % 2, i);
        }

        return hash;
    }

    int hashFunction6()
    {
        int numChar = str.size();
        int hash = 0;
        for(int i = 0; i < numChar; i++)
        {
            hash += str[i] + pow(i % 2, i % 2);
        }

        return hash;
    }
};