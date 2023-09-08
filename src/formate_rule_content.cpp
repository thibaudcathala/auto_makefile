#include "auto_makefile.hpp"
#include <filesystem>

static std::string get_path(const auto_mk::ffile_t &current)
{
    if (current.is_file) {
        return current.path;
    } else {
        return "$(" + current.rule_name.substr(0, current.size_rule_name) + ')';
    }
}

static void proccess_rule(std::vector<std::string> &result,
    auto_mk::ffile_t node, int nb_tab)
{
    sort_rule_content(node);
    auto prev_end = std::prev(node.children.end());

    result.push_back(node.rule_name);
    for (auto current = node.children.begin(); current != node.children.end(); ++current) {
        if (current == node.children.begin()) {
            result.back() += get_path(*current);
        } else {
            result.push_back(std::string(nb_tab, '\t') + get_path(*current));
        }
        if (current != prev_end) {
            result.back() += " \\";
        }
    }
}

static void for_each_rule(const auto_mk::ffile_t &node, std::vector<std::string> &result, int nb_tab)
{
    for (auto child = node.children.rbegin(); child != node.children.rend(); ++child) {
        for_each_rule(*child, result, nb_tab);
    }
    if (!node.is_file && node.parent != nullptr) {
        proccess_rule(result, node, nb_tab);
        result.push_back("");
    }
}

void formate_rule_content(std::vector<std::string> &result,
    const auto_mk::ffile_t &root, int nb_tab)
{
    std::cout << "_______________Result_______________\n";
    for_each_rule(root, result, nb_tab);
    proccess_rule(result, root, nb_tab);
    for (auto &line : result) {
        std::cout << line << "\n";
    }
    std::cout << "____________________________________\n";
}
