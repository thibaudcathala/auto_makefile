#include "auto_makefile.hpp"
#include <filesystem>

static int get_nb_of_tab(const std::string &nb_tab_str)
{
    int nb_tab = 0;

    try {
        nb_tab = std::stoi(nb_tab_str);
        if (nb_tab < 0 || nb_tab > 100) {
            throw std::runtime_error("can't be negative or > 100");
        }
    } catch(const std::exception &error) {
        static_cast<void>(error);
        throw auto_mk::invalid_nb_of_tab(nb_tab_str);
    }
    return nb_tab;
}

static void add_tab(std::string &rule_name, size_t nb_tab)
{
    int nb_tab_to_add = nb_tab - (rule_name.size() / 4);

    if (rule_name.size() < nb_tab * 4) {
        for (int i = 0; i < nb_tab_to_add - 1; ++i) {
            rule_name.push_back('\t');
        }
    }
    rule_name.push_back('=');
    rule_name.push_back('\t');
}

static void formate_rule_name(auto_mk::ffile_t &rule, const std::vector<std::string> &rule_formatring, int nb_tab)
{
    for (size_t i = 0; i < rule_formatring.size(); ++i) {
        if (rule_formatring[i] == auto_mk::var_fold) {
            rule.rule_name += rule.folder;
        } else if (rule_formatring[i] == auto_mk::var_subfold) {
            rule.rule_name += rule.sub_folder;
        } else {
            rule.rule_name += rule_formatring[i];
        }
    }
    std::transform(rule.rule_name.begin(), rule.rule_name.end(), rule.rule_name.begin(), ::toupper);
    rule.size_rule_name = rule.rule_name.size();
    add_tab(rule.rule_name, nb_tab);
}

static void for_each_folder(auto_mk::ffile_t &node, const std::vector<std::string> &rule_formatring, int nb_tab,
    std::function<void(auto_mk::ffile_t &, const std::vector<std::string> &, int)> method)
{
    if (!node.is_file && node.parent != nullptr) {
        method(node, rule_formatring, nb_tab);
    }
    for (auto &child : node.children) {
        for_each_folder(child, rule_formatring, nb_tab, method);
    }
}

std::vector<std::string> formate_rule(auto_mk::ffile_t &root, const auto_mk::section_t &section)
{
    std::vector<std::string> result;
    int nb_tab = get_nb_of_tab(section.arg[auto_mk::NB_TAB][0]);

    root.rule_name = section.arg[auto_mk::ROOT_RULE][0];
    add_tab(root.rule_name, nb_tab);
    for_each_folder(root, section.arg[auto_mk::SUBFOLD_RULE_NAME], nb_tab,
        [](auto_mk::ffile_t &node, const std::vector<std::string> &rule_formatring, int nb_tab) {
        formate_rule_name(node, rule_formatring, nb_tab);
    });
    formate_rule_content(result, root, nb_tab);
    return result;
}
