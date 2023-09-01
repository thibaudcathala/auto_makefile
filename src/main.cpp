#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "auto_makefile.hpp"

bool is_all_param_fill(const std::vector<auto_mk::param_t> &param)
{
    for (size_t i = 0; i < param.size(); ++i) {
        if (param[i].str.empty()) {
            return false;
        }
    }
    return true;
}

void init_param_list(std::vector<auto_mk::param_t> &param)
{
    for (size_t i = 0; i < auto_mk::NB_PARAM; ++i) {
        param[i] = auto_mk::param_t {static_cast<auto_mk::param_e>(i)};
    }
}

void launch_makefile_parsing(std::vector<std::string> &file_content)
{
    std::vector<auto_mk::param_t> param(auto_mk::NB_PARAM);

    init_param_list(param);
    for (size_t i = 0; i < file_content.size(); ++i) {
        for (size_t j = 0; j < auto_mk::NB_PARAM; ++j) {
            get_param(file_content, i, param[j]);
        }
        if (is_all_param_fill(param)) {
            break;
        }
    }
    parse_makefile_param(param);
//    std::vector<auto_mk::section_t> &section ;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << auto_mk::usage;
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        try {
            std::vector<std::string> file_content = get_file_content(argv[i]);

            launch_makefile_parsing(file_content);
        } catch(const std::exception &error) {
            std::cerr << error.what() << '\n';
        }
    }
    return 0;
}
