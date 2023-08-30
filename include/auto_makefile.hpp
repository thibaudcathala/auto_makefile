#ifndef AUTO_MAKEFILE_H
    #define AUTO_MAKEFILE_H

    #include <iostream>
    #include <string>
    #include <string_view>
    #include <array>
    #include <vector>
    #include <stdexcept>

namespace auto_mk {

    extern const std::string usage;

    extern const std::string marker;

    enum param_e {
        ROOT_RULE,
        FILE_EXT,
        SUBFOLD_RULE_NAME,
        NB_PARAM
    };

    extern const std::vector<std::string> param_list;

    extern const std::string var_fold;
    extern const std::string var_unfold;

    struct section_t {
        int start_line;
        int end_line;
        std::string root_rule;
        std::vector<std::string> file_ext;
        std::string subfold_rule_name;

        section_t() : start_line(-1), end_line(-1) {}
    };

    std::runtime_error fail_to_open_file(const std::string filename);
    std::runtime_error missing_colon(const std::string param);
    std::runtime_error missing_semicolon(const std::string param);
    std::runtime_error variable_not_found(const std::string var);
}

void check_arg_validity(int argc);
std::vector<std::string> get_file_content(std::string filename);
void get_param(const std::vector<std::string> &file_content, size_t &index,
    std::string &param, auto_mk::param_e param_index);
void parse_makefile_param(const std::vector<std::string> &param);

#endif /* AUTO_MAKEFILE_H */
