#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "auto_makefile.hpp"

std::vector<std::string> get_file_content(const std::string &filename)
{
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        throw auto_mk::fail_to_open_file(filename);
    }

    auto_mk::current_filename = filename;
    std::vector<std::string> file_content;
    std::string line;

    while (std::getline(input_file, line)) {
        file_content.push_back(line);
    }
    return file_content;
}
