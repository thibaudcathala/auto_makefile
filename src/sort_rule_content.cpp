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
            return node_a.last_write_time < node_b.last_write_time;
        }
    });
}
