#ifndef AUTO_MAKEFILE_H
    #define AUTO_MAKEFILE_H

    #include <iostream>
    #include <string>
    #include <string_view>
    #include <array>
    #include <vector>
    #include <memory>
    #include <stdexcept>
    #include <functional>

namespace auto_mk {

    extern const std::string usage;

    extern const std::string marker;

    enum param_e {
        ROOT_RULE,
        PATH,
        FILE_EXT,
        SUBFOLD_RULE_NAME,
        NB_PARAM
    };

    enum arg_nb_e {
        UNLIMITED,
        ONE
    };

    extern const std::vector<std::string> param_list;
    extern const std::vector<std::string> param_delimiter;
    extern const std::vector<size_t> param_arg_nb;

    extern const std::string var_fold;
    extern const std::string var_unfold;

    struct param_t {
        std::string str;
        size_t pos;
        auto_mk::param_e index;
        bool in_param;

        param_t() :
            pos(0), index(static_cast<param_e>(0)), in_param(false) {}
        param_t(auto_mk::param_e param_index) :
            pos(0), index(param_index), in_param(false) {}
    };

    struct section_t {
        int start_line;
        int end_line;
        std::vector<std::vector<std::string>> arg;

        section_t() : start_line(-1), end_line(-1) {}
        section_t(size_t nb_arg) : start_line(-1), end_line(-1), arg(nb_arg) {}
    };

    std::runtime_error fail_to_open_file(const std::string &filename);
    std::runtime_error missing_colon(const std::string &param);
    std::runtime_error missing_semicolon(const std::string &param);
    std::runtime_error variable_not_found(const std::string &var);
    std::runtime_error invalid_nb_of_arg(const std::string &param, size_t nb_arg, size_t nb_expected);
    std::runtime_error root_rule_not_found(const std::string &rule_name);
    std::runtime_error marker_not_found(const std::string &marker, const std::string &rule_name);
    std::runtime_error invalid_nb_of_section_arg(
        size_t param_index, size_t section_index, size_t nb_arg, size_t nb_expected);
}

void check_arg_validity(int argc);
std::vector<std::string> get_file_content(std::string filename);
void get_param(const std::vector<std::string> &file_content,
    size_t &index, auto_mk::param_t &param);
void parse_makefile_param(const std::vector<auto_mk::param_t> &param,
    std::vector<auto_mk::section_t> &section);
std::vector<std::string> split_string(const std::string &str, const std::string &delimiter);
void print_vector(const std::vector<std::string> &vector);
void get_makefile_rule_pos(const std::vector<std::string> &file_content,
    std::vector<auto_mk::section_t> &section);
void generate_rule_content(std::vector<std::string> &file_content,
    std::vector<auto_mk::section_t> &section);

#endif /* AUTO_MAKEFILE_H */
