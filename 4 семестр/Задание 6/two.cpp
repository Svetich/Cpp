#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream outf("two_file.cpp");
   
    outf << "abcd\n";
    outf << "efgh\n";
    outf << "1234\n";
    outf << "5678\n";
    outf << "ijkl\n";
    outf << "mnop\n"; 

    outf.close();

    int number;

    cin >> number;
    
    ifstream inf("two_file.cpp");
    inf.seekg((number - 1) * 5, ios::cur);
    
    string strInput;
    getline(inf, strInput);

    cout << strInput << endl;


    return 0;
}