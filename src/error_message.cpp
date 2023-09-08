#include "auto_makefile.hpp"
#include "my_color.hpp"

namespace auto_mk {

    std::runtime_error fail_to_open_file(const std::string &filename)
    {
        return std::runtime_error("auto_makefile: " + color::red + "Failed to open: " + filename + "." + color::reset);
    }

    std::runtime_error missing_colon(const std::string &param)
    {
        return std::runtime_error("auto_makefile: " + color::red + "missing ':' between \"" + param + "\" variable and value." + color::reset);
    }

    std::runtime_error missing_semicolon(const std::string &param)
    {
        return std::runtime_error("auto_makefile: " + color::red + "missing ';' at the end of \"" + param + "\" parameter." + color::reset);
    }

    std::runtime_error variable_not_found(const std::string &var)
    {
        return std::runtime_error("auto_makefile: " + color::red + color::red + "\"" + var + "\""
            + color::reset + " variable not found." + color::reset);
    }

    std::runtime_error invalid_nb_of_arg(const std::string &param, size_t nb_arg, size_t nb_expected)
    {
        return std::runtime_error("auto_makefile: " + color::red + param + " has " + std::to_string(nb_arg) +
            " argument but expecte " + std::to_string(nb_expected) + "." + color::reset);
    }

    std::runtime_error root_rule_not_found(const std::string &rule_name)
    {
        return std::runtime_error("auto_makefile: " + color::red + "The \"" + rule_name + "\" rule where not fond." + color::reset);
    }

    std::runtime_error marker_not_found(const std::string &marker, const std::string &rule_name)
    {
        return std::runtime_error("auto_makefile: " + color::red + "The " + marker + " marker of the rule \"" + rule_name + "\" where not fond." + color::reset);
    }

    std::runtime_error invalid_nb_of_section_arg(
        size_t param_index, size_t section_index, size_t nb_arg, size_t nb_expected)
    {
        if (nb_expected == 0) {
            return std::runtime_error("auto_makefile: " + color::red + auto_mk::param_list[param_index] + "[" +
                std::to_string(section_index) + "] has " + std::to_string(nb_arg) +
                " argument but expecte at least " + std::to_string(nb_expected + 1) + "." + color::reset);
        } else {
            return std::runtime_error("auto_makefile: " + color::red + auto_mk::param_list[param_index] + "[" +
                std::to_string(section_index) + "] has " + std::to_string(nb_arg) +
                " argument but expecte " + std::to_string(nb_expected) + "." + color::reset);
        }
    }

    std::runtime_error invalid_folder_path(const std::string &path)
    {
        return std::runtime_error("auto_makefile: " + color::red + "Invalid folder path: \"" + path + "\"." + color::reset);
    }

    std::runtime_error invalid_nb_of_tab(const std::string &nb_tab)
    {
        return std::runtime_error("auto_makefile: " + color::red + nb_tab + " is not a valid number of tab." + color::reset);
    }
}
