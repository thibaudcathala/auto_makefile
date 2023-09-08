#include "auto_makefile.hpp"

static void check_param_validity(const std::vector<auto_mk::param_t> &param)
{
    for (size_t i = 0; i < param.size(); ++i) {
        if (param[i].str.empty()) {
            throw auto_mk::variable_not_found(auto_mk::param_list[i]);
        }
    }
}

static void split_all_arg(
    const std::vector<auto_mk::param_t> &param,
    std::vector<std::vector<std::string>> &word)
{
    for (size_t i = 0; i < param.size(); ++i) {
        word.push_back(split_string(param[i].str, ","));
    }
    for (size_t i = 0; i < param.size(); ++i) {
        if (word[i].size() != word.at(0).size()) {
            throw auto_mk::invalid_nb_of_arg(
                auto_mk::param_list[param[i].index],
                word[i].size(), word[0].size());
        }
    }
}

static void fill_section_arg(
    const std::vector<auto_mk::param_t> &param,
    std::vector<auto_mk::section_t> &section)
{
    std::vector<std::vector<std::string>> word;

    split_all_arg(param, word);
    for (size_t i = 0; i < word.at(0).size(); ++i) {
        auto_mk::section_t current_sec(param.size());

        for (size_t j = 0; j < param.size(); ++j) {
            current_sec.arg[j].push_back(word[j][i]);
        }
        section.push_back(current_sec);
    }
}

static void clean_section_arg(
    const std::vector<auto_mk::param_t> &param,
    std::vector<auto_mk::section_t> &section)
{
    for (size_t i = 0; i < section.size(); ++i) {
        for (size_t j = 0; j < param.size(); ++j) {
            section[i].arg[j] = split_string(section[i].arg[j].at(0), auto_mk::param_delimiter[j]);
            if ((auto_mk::param_arg_nb[j] != auto_mk::UNLIMITED
            && auto_mk::param_arg_nb[j] != section[i].arg[j].size())
            || section[i].arg[j].size() == 0) {
                throw auto_mk::invalid_nb_of_section_arg(j, i, section[i].arg[j].size(), auto_mk::param_arg_nb[j]);
            }
        }
    }
}

void parse_makefile_param(
    const std::vector<auto_mk::param_t> &param,
    std::vector<auto_mk::section_t> &section)
{
    check_param_validity(param);
    fill_section_arg(param, section);
    clean_section_arg(param, section);
}
