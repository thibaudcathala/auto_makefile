#include "auto_makefile.hpp"

void sort_rule_content(auto_mk::ffile_t &node)
{
    node.children.sort([](const auto_mk::ffile_t &node_a, const auto_mk::ffile_t &node_b)
    {
        if (node_a.is_file && !node_b.is_file) {
            return true;
        } else if (!node_a.is_file && node_b.is_file) {
            return false;
        } else {
            return node_a.creation_date < node_b.creation_date;
        }
    });
}
