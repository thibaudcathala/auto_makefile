#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "auto_makefile.hpp"

static void get_line_content(char c, bool &in_param,
    std::string &param, auto_mk::param_e param_index)
{
    if (c == ';') {
        if (!in_param) {
            throw auto_mk::missing_colon(auto_mk::param_list[param_index]);
        }
        return;
    }
    if (in_param) {
        if (in_param && c == '#') {
            throw auto_mk::missing_semicolon(auto_mk::param_list[param_index]);
        }
        param.push_back(c);
    }
    if (c == ':') {
        in_param = true;
    }
}

static void get_complete_param_line(const std::vector<std::string> &file_content,
    size_t &index, std::string &param, size_t pos, auto_mk::param_e param_index)
{
    bool in_param = false;

    for (; index < file_content.size(); ++index) {
        for (size_t j = pos; j < file_content[index].size(); ++j) {
            get_line_content(file_content[index][j], in_param, param, param_index);
        }
        if (!in_param) {
            throw auto_mk::missing_colon(auto_mk::param_list[param_index]);
        }
        pos = 0;
    }
    throw auto_mk::missing_semicolon(auto_mk::param_list[param_index]);;
}

void get_param(const std::vector<std::string> &file_content, size_t &index,
    std::string &param, auto_mk::param_e param_index)
{
    size_t pos_comment = file_content[index].find('#');
    size_t pos_param;

    if (pos_comment != std::string::npos) {
        pos_param = file_content[index].find(auto_mk::param_list[param_index]);
        if (pos_param != std::string::npos && pos_param > pos_comment) {
            get_complete_param_line(file_content, index, param, pos_param, param_index);
        }
    }
}
