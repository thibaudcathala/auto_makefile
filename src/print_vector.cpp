#include "auto_makefile.hpp"

void print_vector(const std::vector<std::string> &vector)
{
    std::cout << "[\"";
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i];
        if (i < vector.size() - 1) {
            std::cout << "\", \"";
        }
    }
    std::cout << "\"]\n";
}
