#include "auto_makefile.hpp"

static bool get_line_content(char c, auto_mk::param_t &param)
{
    if (c == ';') {
        if (!param.in_param) {
            throw auto_mk::missing_colon(auto_mk::param_list[param.index]);
        }
        return true;
    }
    if (param.in_param) {
//        if (c == '#') {
//            throw auto_mk::missing_semicolon(auto_mk::param_list[param.index]);
//        }
        param.str.push_back(c);
    }
    if (c == ':') {
        param.in_param = true;
    }
    return false;
}

bool process_line(const std::string &line, auto_mk::param_t &param)
{
    for (size_t j = param.pos; j < line.size(); ++j) {
        if (get_line_content(line[j], param)) {
            return true;
        }
    }
    if (!param.in_param) {
        throw auto_mk::missing_colon(auto_mk::param_list[param.index]);
    }
    param.pos = 0;
    return false;
}

static void get_complete_param_line(
    const std::vector<std::string> &file_content,
    size_t &index, auto_mk::param_t &param)
{
    for (; index < file_content.size(); ++index) {
        if (process_line(file_content[index], param)) {
            return;
        }
    }
    throw auto_mk::missing_semicolon(auto_mk::param_list[param.index]);
}

void get_param(const std::vector<std::string> &file_content,
    size_t &index, auto_mk::param_t &param)
{
    size_t pos_comment = file_content[index].find('#');

    if (pos_comment != std::string::npos) {
        param.pos = file_content[index].find(auto_mk::param_list[param.index]);
        if (param.pos != std::string::npos && param.pos > pos_comment) {
            get_complete_param_line(file_content, index, param);
        }
    }
}
