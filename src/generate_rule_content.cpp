#include "auto_makefile.hpp"
#include <filesystem>

static void get_file_from_path(const std::string &path, const std::vector<std::string> &result)
{
    std::filesystem::path folder_path = std::filesystem::current_path();
    folder_path += std::string("/");
    folder_path += path;

    std::cout << "Path: " << folder_path << "\n";
    if (!std::filesystem::exists(folder_path) || !std::filesystem::is_directory(folder_path)) {
        std::cerr << "Error: Invalid folder path." << std::endl;
        return;
    }
    for (const auto &entry : std::filesystem::recursive_directory_iterator(folder_path)) {
        if (std::filesystem::is_directory(entry.status())) {
            std::cout << "Directory: " << entry.path() << std::endl;
        } else if (std::filesystem::is_regular_file(entry.status())) {
            std::cout << "File: " << entry.path() << std::endl;
        }
    }
}

void generate_rule_content(std::vector<std::string> &file_content,
    std::vector<auto_mk::section_t> &section)
{
    std::vector<std::string> result;

    for (size_t i = 0; i < section.size(); ++i) {
        get_file_from_path(section[i].arg[auto_mk::PATH][0], result);
    }
}
