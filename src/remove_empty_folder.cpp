#include "auto_makefile.hpp"
#include <filesystem>

void remove_empty_folder(auto_mk::ffile_t &node)
{
    std::list<auto_mk::ffile_t>::iterator current_node = node.children.begin();
    while (current_node != node.children.end()) {
        remove_empty_folder(*current_node);

        if (!current_node->is_file && current_node->children.empty()) {
            current_node = node.children.erase(current_node);
        } else {
            ++ current_node;
        }
    }
}
