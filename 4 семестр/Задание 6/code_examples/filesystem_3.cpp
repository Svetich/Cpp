#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char ** argv)
{
	system("chcp 1251");

	// см. также exists

	auto path = std::filesystem::current_path();

	std::filesystem::create_directory(path / "directory_1");

	std::filesystem::create_directory(path / "directory_1", path);

	std::filesystem::create_directories(path / "directory_2" / "directory_3");

	std::filesystem::create_directories("A/B/C");
	std::fstream("A/file_1.txt", std::ios::out).put('a');
	std::filesystem::copy("A/file_1.txt", "A/file_2.txt");
	std::filesystem::copy("A/B", "A/BB"); // copy directory (non-recursive)
	std::filesystem::copy("A", "AA", std::filesystem::copy_options::recursive);
	std::filesystem::rename("AA", "new_name");
	//std::filesystem::remove_all("AA");
	//std::filesystem::remove_all("A");

	// см. также copy_symlink, copy_file

	system("pause");

	return EXIT_SUCCESS;
}