#include "auto_makefile.hpp"
#include <filesystem>
#include "my_color.hpp"

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

        if (entry.is_directory()) {
            fill_fold_and_subfold(node);
            manage_entry(entry, &node, current_path, file_ext);
        }
        if (entry.is_regular_file() && is_right_file_ext(entry.path(), file_ext)) {
            node.last_write_time = entry.last_write_time();
            node.is_file = true;
            parent->children.push_back(node);
        } else if (entry.is_directory()) {
            node.last_write_time = entry.last_write_time();
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

void generate_rule_content(std::list<std::string> &file_content,
    std::vector<auto_mk::section_t> &section)
{
    for (size_t i = 0; i < section.size(); ++i) {
        auto_mk::ffile_t root = get_file_from_path(section[i].arg[auto_mk::PATH][0], section[i].arg[auto_mk::FILE_EXT]);
        remove_empty_folder(root);
        insert_rule_in_makefile(file_content, formate_rule(root, section[i]), section[i].start_line, section[i].end_line);
    }
}
