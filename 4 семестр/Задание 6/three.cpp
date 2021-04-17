/*Напишите программу, которая определяет содержимое заданной пользователем
существующей на компьютере директории,
это можно сделать в цикле
for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
Для файлов и папок в директории выведите название, тип (директория
std::filesystem::is_directory(path) или обычный файл std::filesystem::is_regular_file(path)) и
время последнего изменения std::filesystem::last_write_time(path).*/

#include <filesystem>
#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    string strPath;
    cin >> strPath;
    
    system("dir");

    auto path = experimental::filesystem::current_path() / "/two.cpp";
    

    for (auto const & entry : experimental2003
    ::filesystem::recursive_directory_iterator(path))
    {
        cout << entry <<endl;
    }

    return 0;
}