#include "auto_makefile.hpp"
#include <filesystem>
#include "my_color.hpp"


#include <sys/types.h>
#include <sys/stat.h>

static bool is_right_file_ext(const std::string &path,
    const std::vector<std::string> &ref_file_ext)
{
    for (size_t i = 0; i < ref_file_ext.size(); ++i) {
        if (path.ends_with(ref_file_ext[i])) {
            return true;
        }
    }
    return false;
}

static void fill_fold_and_subfold(auto_mk::ffile_t &node)
{
    node.folder = node.path.parent_path().filename();
    node.sub_folder = node.path.filename();
}

static void manage_entry(const std::filesystem::path &folder_path, auto_mk::ffile_t *parent,
    const std::filesystem::path &current_path,
    const std::vector<std::string> &file_ext)
{
    for (const auto &entry : std::filesystem::directory_iterator(folder_path)) {
        auto_mk::ffile_t node(std::filesystem::relative(entry.path(), current_path), parent);
        struct stat file_stat;

        if (entry.is_directory()) {
            fill_fold_and_subfold(node);
            manage_entry(entry, &node, current_path, file_ext);
        }
        if (stat(entry.path().c_str(), &file_stat) == 0) {
            node.creation_date = file_stat.st_ctime;
        }
        if (entry.is_regular_file() && is_right_file_ext(entry.path(), file_ext)) {
            node.is_file = true;
            parent->children.push_back(node);
        } else if (entry.is_directory()) {
            fill_fold_and_subfold(node);
            parent->children.push_back(node);
        }
    }
}

static auto_mk::ffile_t get_file_from_path(const std::string &path,
    const std::vector<std::string> &file_ext)
{
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path folder_path = current_path / path;

    if (!std::filesystem::exists(folder_path)
    || !std::filesystem::is_directory(folder_path)) {
        throw auto_mk::invalid_folder_path(folder_path);
    }
    auto_mk::ffile_t root(folder_path, nullptr);
    manage_entry(folder_path, &root, current_path, file_ext);
    return root;
}

void printTree(const auto_mk::ffile_t &node, int level = 0)
{
    for (int i = 0; i < level; ++i) {
        std::cout << "    "; // Indentation to represent the tree structure
    }
    if (!node.is_file) {
        std::cout << color::cyan << node.path << ", fold: " << node.folder << ", sub_fold: " <<
            node.sub_folder << ", time: " << node.creation_date << color::reset << "\n";
    } else {
        std::cout << node.path << ", time: " << node.creation_date << "\n";
    }
    for (const auto &child : node.children) {
        printTree(child, level + 1); // Recursive call to print children
    }
}

void generate_rule_content(std::vector<std::string> &file_content,
    std::vector<auto_mk::section_t> &section)
{
    for (size_t i = 0; i < section.size(); ++i) {
        auto_mk::ffile_t root = get_file_from_path(section[i].arg[auto_mk::PATH][0], section[i].arg[auto_mk::FILE_EXT]);
        printTree(root);
        remove_empty_folder(root);
        std::cout << "-------------------------------------------------------------------\n";
        printTree(root);
        std::cout << "-------------------------------------------------------------------\n";
        insert_rule_in_makefile(file_content, formate_rule(root, section[i]), section[i].start_line, section[i].end_line);
    }
}
