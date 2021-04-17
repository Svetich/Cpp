#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

vector <string> read_file()
{
    ifstream iofile("file_one.cpp");
    vector <string> all_file;
    while (iofile)
    {
        string strInput;
        getline(iofile, strInput);
        all_file.push_back(strInput);
    }

    iofile.close();

    return all_file;
}


vector <int> create_com(vector <string> all_file)
{
    vector <int> com_1; // //
    vector <int> com_2; // /*
    vector <int> com_3; // */

    for (int i = 0; i < all_file.size(); i++)
    {
        if (all_file[i].find("//") != string::npos)
        {
            com_1.push_back(i);
        }

        if (all_file[i].find("/*") != string::npos)
        {
            com_2.push_back(i);
        }

        if (all_file[i].find("*/") != string::npos)
        {
            com_3.push_back(i);
        }
    }   

    for (int i = 0; i < com_2.size(); i++)
    {
        cout << com_2.size() << endl;
        cout << com_3.size() << endl;
        int com = com_3[i] - com_2[i];  

        for (int j = com_2[i]; j <= com_3[i]; j++)
        {
            com_1.push_back(j);
        }        
    }
    return com_1;
}

vector <string> remove(vector <int> com, vector <string> all_file)
{
    for (int i = 0; i < com.size(); i++)
    {
        cout << com[i] <<endl;
        cout << all_file[com[i]] <<endl;
        all_file[com[i]] = string("");
        cout << all_file[com[i]] <<endl;
    }    
    return all_file;
}

int main()
{
    vector <string> all_file = read_file();
    vector <int> com = create_com(all_file);
        
    vector <string> new_file = remove(com, all_file);

    fstream iofile("file_one.cpp", ios::trunc | ios::out);

    for (int i = 0; i < new_file.size(); i++)
    {
        iofile << new_file[i] <<endl;
    }

    iofile.close();
    return 0;
}