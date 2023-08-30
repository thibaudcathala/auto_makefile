#include "auto_makefile.hpp"
#include "my_color.hpp"

namespace auto_mk {

    std::runtime_error fail_to_open_file(const std::string filename)
    {
        return std::runtime_error("Failed to open: " + filename + ".");
    }

    std::runtime_error missing_colon(const std::string param)
    {
        return std::runtime_error("missing ':' between \"" + param + "\" variable and value.");
    }

    std::runtime_error missing_semicolon(const std::string param)
    {
        return std::runtime_error("missing ';' at the end of \"" + param + "\" parameter.");
    }

    std::runtime_error variable_not_found(const std::string var)
    {
        return std::runtime_error(color::red + "\"" + var + "\""
            + color::reset + "\" variable not found.");
    }
}
