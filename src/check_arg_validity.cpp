#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "auto_makefile.hpp"

void check_arg_validity(int argc)
{
    if (argc < 2) {
        throw std::runtime_error(auto_mk::usage);
    }
}
