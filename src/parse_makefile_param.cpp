#include "auto_makefile.hpp"
#include "my_color.hpp"

std::vector<std::string> split_string(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> sub_strings;
    size_t start = 0;

    for (size_t i = 0; i <= str.size(); ++i) {
        if (i == str.size() || delimiter.find(str[i]) != std::string::npos) {
            if (i > start) {
                sub_strings.push_back(str.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    return sub_strings;
}

void parse_makefile_param(const std::vector<std::string> &param)
{
    for (size_t i = 0; i < param.size(); ++i) {
        if (param[i].empty()) {
            throw auto_mk::variable_not_found(auto_mk::param_list[i]);
        }
        std::cout << auto_mk::param_list[i] << " str : " << param[i] << "\n";
    }
}
