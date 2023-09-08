#include "auto_makefile.hpp"

namespace auto_mk {

    std::string current_filename;

    const std::string usage = "Usage: ./auto_makefile [Makefile] ...\n";

    const std::string marker = "#//";

    const std::vector<std::string> param_list = {
        "root",
        "path",
        "file_ext",
        "subfold_rule_name",
        "nb_tab"
    };

    const std::vector<size_t> param_arg_nb = {
        ONE,
        ONE,
        UNLIMITED,
        UNLIMITED,
        ONE
    };

    const std::vector<std::string> param_delimiter = {
        " \t\n\"\'",
        " \t\n\"\'",
        " \t\n\"\'",
        " \t\n\"\'+",
        " \t\n\"\'"
    };

    const std::string var_fold = "{FOLD}";
    const std::string var_subfold = "{SUBFOLD}";

    std::vector<std::string> used_rule_name;
    int rule_name_i = 1;
}
