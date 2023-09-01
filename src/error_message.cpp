#include "auto_makefile.hpp"
#include "my_color.hpp"

namespace auto_mk {

    std::runtime_error fail_to_open_file(const std::string &filename)
    {
        return std::runtime_error("Failed to open: " + filename + ".");
    }

    std::runtime_error missing_colon(const std::string &param)
    {
        return std::runtime_error("missing ':' between \"" + param + "\" variable and value.");
    }

    std::runtime_error missing_semicolon(const std::string &param)
    {
        return std::runtime_error("missing ';' at the end of \"" + param + "\" parameter.");
    }

    std::runtime_error variable_not_found(const std::string &var)
    {
        return std::runtime_error(color::red + "\"" + var + "\""
            + color::reset + " variable not found.");
    }

    std::runtime_error invalid_nb_of_arg(const std::string &param, size_t nb_arg, size_t nb_expected)
    {
        return std::runtime_error(param + " has " + std::to_string(nb_arg) +
            " argument but expecte " + std::to_string(nb_expected) + ".");
    }

    std::runtime_error root_rule_not_found(const std::string &rule_name)
    {
        return std::runtime_error("The \"" + rule_name + "\" rule where not fond.");
    }

    std::runtime_error marker_not_found(const std::string &marker, const std::string &rule_name)
    {
        return std::runtime_error("The " + marker + " marker of the rule \"" + rule_name + "\" where not fond.");
    }

    std::runtime_error invalid_nb_of_section_arg(
        size_t param_index, size_t section_index, size_t nb_arg, size_t nb_expected)
    {
        if (nb_expected == 0) {
            return std::runtime_error(auto_mk::param_list[param_index] + "[" +
                std::to_string(section_index) + "] has " + std::to_string(nb_arg) +
                " argument but expecte at least " + std::to_string(nb_expected + 1) + ".");
        } else {
            return std::runtime_error(auto_mk::param_list[param_index] + "[" +
                std::to_string(section_index) + "] has " + std::to_string(nb_arg) +
                " argument but expecte " + std::to_string(nb_expected) + ".");
        }
    }
}
