#include "auto_makefile.hpp"

static size_t search_root_rule(const std::string &rule_name,
    const std::vector<std::string> &file_content)
{
    for (size_t i = 0; i < file_content.size(); ++i)
    {
        if (file_content[i].compare(0, rule_name.size(), rule_name) == 0) {
            if (file_content[i][rule_name.size()] == ' '
            || file_content[i][rule_name.size()] == '\t'
            || file_content[i][rule_name.size()] == '=') {
                return i;
            }
        }
    }
    throw auto_mk::root_rule_not_found(rule_name);
}

static void search_start_end(size_t rule_pos,
    const std::vector<std::string> &file_content,
    auto_mk::section_t &section)
{
    for (int i = rule_pos; i >= 0; --i) {
        if (file_content[i].compare(0, auto_mk::marker.size(), auto_mk::marker) == 0) {
            section.start_line = i;
            break;
        }
    }
    if (section.start_line == -1) {
        throw auto_mk::marker_not_found("top", section.arg[auto_mk::ROOT_RULE][0]);
    }
    for (size_t i = rule_pos; i < file_content.size(); ++i) {
        if (file_content[i].compare(0, auto_mk::marker.size(), auto_mk::marker) == 0) {
            section.end_line = i;
            break;
        }
    }
    if (section.end_line == -1) {
        throw auto_mk::marker_not_found("bottom", section.arg[auto_mk::ROOT_RULE][0]);
    }
}

void get_makefile_rule_pos(const std::vector<std::string> &file_content,
    std::vector<auto_mk::section_t> &section)
{
    for (size_t i = 0; i < section.size(); ++i) {
        search_start_end(search_root_rule(
            section[i].arg[auto_mk::ROOT_RULE][0], file_content), file_content, section[i]);
    }
}
