#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

auto compute_file_size(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path))
	{
		auto file_size = std::filesystem::file_size(path);

		if (file_size != static_cast <uintmax_t> (-1))
		{
			return file_size;
		}
	}

	return static_cast <uintmax_t> (-1);
}

auto compute_directory_size(const std::filesystem::path & path)
{
	uintmax_t size = 0ULL;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
			{
				auto file_size = std::filesystem::file_size(entry);

				if (file_size != static_cast <uintmax_t> (-1))
				{
					size += file_size;
				}
			}
		}
	}

	return size;
}

void view_directory(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			std::cout << file_name << std::endl;
		}
	}
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

	std::cout << compute_file_size("./Source.cpp") << std::endl;

	std::cout << compute_directory_size(std::filesystem::current_path()) << std::endl;

	view_directory(std::filesystem::current_path());

	system("pause");

	return EXIT_SUCCESS;
}