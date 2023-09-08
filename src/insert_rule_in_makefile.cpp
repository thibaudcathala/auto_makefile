#include "auto_makefile.hpp"
#include "my_color.hpp"

static void remove_existing_rule(std::list<std::string> &new_makefile,
    std::list<std::string>::iterator start_line,
    std::list<std::string>::iterator end_line)
{
    new_makefile.erase(std::next(start_line), end_line);
}

static void insert_new_rule(std::list<std::string> &new_makefile,
    const std::vector<std::string> &result,
    std::list<std::string>::iterator &insert_pos)
{
    ++ insert_pos;
    for (size_t i = 0; i < result.size(); ++i) {
        new_makefile.insert(insert_pos, result[i]);
    }
}

static void insert_new_rule_in_makefile(const std::string &filename,
    const std::list<std::string> &new_makefile)
{
    std::ofstream out_makefile(filename);

    if (!out_makefile) {
        throw auto_mk::fail_to_open_file(filename);
    }
    for (const std::string &line : new_makefile) {
        out_makefile << line << '\n';
    }
}

void insert_rule_in_makefile(std::list<std::string> &new_makefile,
    const std::vector<std::string> &result,
    std::list<std::string>::iterator start_line,
    std::list<std::string>::iterator end_line)
{
    std::list<std::string>::iterator insert_pos = start_line;

    remove_existing_rule(new_makefile, start_line, end_line);
    insert_new_rule(new_makefile, result, insert_pos);
    insert_new_rule_in_makefile(auto_mk::current_filename, new_makefile);
    std::cout << "--- MAKEFILE ---\n";
    for (auto &i : new_makefile) {
        std::cout << i << "\n";
    }
    std::cout << "----------------\n";
}
