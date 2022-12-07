#include <utility>

#include "solution.h"

enum class folder_type {
    folder,
    file
};

struct folder_entry {
    folder_type type;
    std::string name;
    uint64_t file_size;
    std::vector<folder_entry *> children;
    folder_entry *parent = nullptr;

    uint64_t size() const {
        return file_size;
    };

    void increase_size_by(unsigned long i) {
        file_size += i;
        if (parent != nullptr) {
            parent->increase_size_by(i);
        }
    }

    void visit_folders(auto& lambda) {
        lambda(this);
        for (auto& c: children) {
            if (c->type == folder_type::folder) {
                c->visit_folders(lambda);
            }
        }
    }
};

struct filesystem {
    folder_entry *root;
    folder_entry *cwd;

    filesystem() {
        root = new folder_entry;
        root->file_size = 0;
        root->type = folder_type::folder;
        root->name = '/';
        root->parent = nullptr;

        cwd = root;
    }

    void switch_to_subdir(std::string name) {
        for (auto& c: cwd->children) {
            if (c->name == name) {
                cwd = c;
                return;
            }
        }
        auto new_dir = add_subdir_to_cwd(name);
        cwd = new_dir;
    }

    void cd(const std::string& argument) {
        if (argument == "/") {
            cwd = root;
        } else if (argument == "..") {
            cwd = cwd->parent;
        } else {
            switch_to_subdir(argument);
        }
    }

    folder_entry *add_subdir_to_cwd(std::string name) const {
        auto *result = new folder_entry;
        result->name = std::move(name);
        result->parent = cwd;
        result->type = folder_type::folder;
        result->file_size = 0;
        cwd->children.push_back(result);

        return result;
    }

    folder_entry *add_file_to_cwd(unsigned long size, std::string name) const {
        auto *result = new folder_entry;
        result->name = std::move(name);
        result->parent = cwd;
        result->type = folder_type::file;
        result->file_size = size;
        cwd->children.push_back(result);
        result->parent->increase_size_by(size);

        return result;
    }

    void visit_folders(auto& lambda) {
        root->visit_folders(lambda);
    }
};

class day7 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        auto fs = map_filesystem(in);
        out << compute_part_1(fs) << std::endl;
        out << compute_part_2(fs) << std::endl;
    }

    static filesystem map_filesystem(std::istream& in) {
        filesystem fs;
        for (std::string line; std::getline(in, line);) {
            auto tokens = aoc::split_string(line, " ");
            bool is_command = tokens[0][0] == '$';
            if (is_command) {
                if (tokens[1] == "cd") {
                    fs.cd(tokens[2]);
                }
            } else {
                if (tokens[0] == "dir") {
                    fs.add_subdir_to_cwd(tokens[1]);
                } else {
                    fs.add_file_to_cwd(std::stoul(tokens[0]), tokens[1]);
                }
            }
        }
        return fs;
    }

    static uint64_t compute_part_1(filesystem& fs) {
        uint64_t part1{0};
        auto visitor = [&part1](folder_entry *dir) {
            if (dir->file_size <= 100000) {
                part1 += dir->file_size;
            }
        };
        fs.visit_folders(visitor);
        return part1;
    }

    static uint64_t compute_part_2(filesystem& fs) {
        std::vector<uint64_t> sizes;
        auto visitor2 = [&sizes](folder_entry *dir) {
            sizes.push_back(dir->file_size);
        };
        fs.visit_folders(visitor2);
        std::sort(std::begin(sizes), std::end(sizes));

        for (auto& s: sizes) {
            if ((70000000ULL - fs.root->file_size + s) >= 30000000ULL) {
                return s;
            }
        }
        return 0; // should not happen
    }
};

int main(int argc, char **argv) {
    day7 solution{};
    return solution.execute(argc, argv);
}
