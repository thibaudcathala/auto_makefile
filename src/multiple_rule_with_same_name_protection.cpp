#include "auto_makefile.hpp"
#include <filesystem>

void multiple_rule_with_same_name_protection(std::string &rule_name)
{
    while (std::find(auto_mk::used_rule_name.begin(),
    auto_mk::used_rule_name.end(), rule_name) != auto_mk::used_rule_name.end()) {
        rule_name += '_' + std::to_string(auto_mk::rule_name_i);
        ++ auto_mk::rule_name_i;
    }
    auto_mk::used_rule_name.push_back(rule_name);
}
