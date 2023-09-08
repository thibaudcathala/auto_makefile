#include "auto_makefile.hpp"
#include "my_color.hpp"

static std::list<std::string> vector_to_list(const std::vector<std::string> vector)
{
    std::list<std::string> list;

    for (const std::string &current : vector) {
        list.push_back(current);
    }
    return list;
}

static void remove_existing_rule(std::list<std::string> &new_makefile,
    std::list<std::string>::iterator &insert_pos, int start_line, int end_line)
{
    int index = 0;
    bool remove_line = false;

    for (auto line = new_makefile.begin(); line != new_makefile.end(); ++line) {
        if (index == end_line) {
            remove_line = false;
        }
        if (remove_line) {
            line = new_makefile.erase(line);
        }
        if (index == start_line) {
            remove_line = true;
            insert_pos = line;
        }
        ++ index;
    }
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

static void insert_new_rule_in_makefile(const std::string &filename, std::list<std::string> &new_makefile)
{
    std::ofstream out_makefile(filename);

    if (!out_makefile) {
        throw auto_mk::fail_to_open_file(auto_mk::current_filename);
    }
    for (const std::string &line : new_makefile) {
        out_makefile << line << '\n';
    }
}

void insert_rule_in_makefile(const std::vector<std::string> &file_content,
    const std::vector<std::string> &result, int start_line, int end_line)
{
    std::list<std::string> new_makefile = vector_to_list(file_content);
    std::list<std::string>::iterator insert_pos;

    remove_existing_rule(new_makefile, insert_pos, start_line, end_line);
    insert_new_rule(new_makefile, result, insert_pos);
    insert_new_rule_in_makefile(auto_mk::current_filename, new_makefile);
    std::cout << "--- MAKEFILE ---\n";
    for (auto &i : new_makefile) {
        std::cout << i << "\n";
    }
    std::cout << "----------------\n";
}
