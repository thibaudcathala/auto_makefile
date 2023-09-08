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

static std::list<std::string>::iterator index_to_iterator(std::list<std::string> &list, int index)
{
    std::list<std::string>::iterator iterator = list.begin();

    std::advance(iterator, index);
    return iterator;
}

static int get_start_pos(size_t rule_pos,
    const std::vector<std::string> &file_content,
    const std::string &rule_name)
{
    int start_line = -1;

    for (int i = rule_pos; i >= 0; --i) {
        if (file_content[i].compare(0, auto_mk::marker.size(), auto_mk::marker) == 0) {
            start_line = i;
            break;
        }
    }
    if (start_line == -1) {
        throw auto_mk::marker_not_found("top", rule_name);
    }
    return start_line;
}

static int get_end_pos(size_t rule_pos,
    const std::vector<std::string> &file_content,
    const std::string &rule_name)
{
    int end_line = -1;

    for (size_t i = rule_pos; i < file_content.size(); ++i) {
        if (file_content[i].compare(0, auto_mk::marker.size(), auto_mk::marker) == 0) {
            end_line = i;
            break;
        }
    }
    if (end_line == -1) {
        throw auto_mk::marker_not_found("bottom", rule_name);
    }
    return end_line;
}

void get_makefile_rule_pos(const std::vector<std::string> &file_content,
    std::list<std::string> &file_content_list,
    std::vector<auto_mk::section_t> &section)
{
    for (size_t i = 0; i < section.size(); ++i) {
        size_t pos_root = search_root_rule(section[i].arg[auto_mk::ROOT_RULE][0], file_content);
        section[i].start_line = index_to_iterator(file_content_list,
            get_start_pos(pos_root, file_content, section[i].arg[auto_mk::ROOT_RULE][0]));
        section[i].end_line = index_to_iterator(file_content_list,
            get_end_pos(pos_root, file_content, section[i].arg[auto_mk::ROOT_RULE][0]));
    }
}
