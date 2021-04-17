#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>

#include "json.hpp"

using nlohmann::json;

int main(int argc, char ** argv)
{
	system("chcp 65001");

	std::filesystem::path path_input = "input.txt";
	std::filesystem::path path_output = "output.txt";

	std::fstream fin(path_input.string(), std::ios::in);

	json j;

	fin >> j;

	fin.close();

	std::cout << std::setw(4) << j << std::endl;

	j["firstName"] = "Ivan";
	j["happy"] = true;
	j.erase("lastName");

	for (auto iterator = j.begin(); iterator != j.end(); ++iterator)
	{
		std::cout << iterator.key() << " : " << iterator.value() << "\n";
	}

	for (auto & element : j.items())
	{
		std::cout << element.key() << " : " << element.value() << "\n";
	}

	for (auto &[key, value] : j.items()) // C++17 bindings
	{
		std::cout << key << " : " << value << "\n";
	}

	std::fstream fout(path_output.string(), std::ios::out);

	fout << std::setw(4) << j;

	system("pause");

	return EXIT_SUCCESS;
}