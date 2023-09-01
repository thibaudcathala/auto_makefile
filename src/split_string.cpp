#include "auto_makefile.hpp"

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
