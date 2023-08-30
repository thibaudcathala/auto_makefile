#include "auto_makefile.hpp"

namespace auto_mk {

    const std::string usage = "Usage: ./auto_makefile [Makefile] ...\n";

    const std::string marker = "#//";

    const std::vector<std::string> param_list = {"root", "file_ext", "subfold_rule_name"};

    const std::string var_fold = "{FOLD}";
    const std::string var_unfold = "{SUBFOLD}";
}
