#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <chrono>

using namespace std;

int main()
{
	filesystem::current_path(filesystem::temp_directory_path());

    for(auto& p: filesystem::recursive_directory_iterator("path"))
    cout << p.path() << filesystem::is_directory;

    if(filesystem::is_regular_file("path")) cout << "обычный файл" << endl;
    if (filesystem::is_directory("path")) cout << "директория" << endl;

    cout << " Время последнего изменения: " << filesystem::last_write_time("path") << endl;

    return 0;
}
