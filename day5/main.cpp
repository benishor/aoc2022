#include "solution.h"

class day5 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        std::array<std::deque<char>, 9> data;
        data[0] = {'N', 'S', 'D', 'C', 'V', 'Q', 'T'};
        data[1] = {'M', 'F', 'V'};
        data[2] = {'F', 'Q', 'W', 'D', 'P', 'N', 'H', 'M'};
        data[3] = {'D', 'Q', 'R', 'T', 'F'};
        data[4] = {'R', 'F', 'M', 'N', 'Q', 'H', 'V', 'B'};
        data[5] = {'C', 'F', 'G', 'N', 'P', 'W', 'Q'};
        data[6] = {'W', 'F', 'R', 'L', 'C', 'T'};
        data[7] = {'T', 'Z', 'N', 'S'};
        data[8] = {'M', 'S', 'D', 'J', 'R', 'Q', 'H', 'N'};

        std::array<std::deque<char>, 9> data2 = data;

        bool reading_moves = false;
        auto move_re = std::regex(R"(^move\s*(\d+)\s*from\s*(\d+)\s*to\s*(\d+)\s*$)");
        for (std::string line; std::getline(in, line);) {
            if (line.empty()) {
                reading_moves = true;
            } else if (reading_moves) {
                std::smatch sm{};
                if (std::regex_match(line, sm, move_re)) {
                    auto how_many = std::stoi(sm.str(1));
                    auto from = std::stoi(sm.str(2)) - 1;
                    auto to = std::stoi(sm.str(3)) - 1;

                    // part 1
                    for (int i = 0; i < how_many; i++) {
                        data[to].push_back(data[from].back());
                        data[from].pop_back();
                    }

                    // part 2
                    std::stack<char> tmp;
                    for (int i = 0; i < how_many; i++) {
                        tmp.push(data2[from].back());
                        data2[from].pop_back();
                    }

                    while (!tmp.empty()) {
                        data2[to].push_back(tmp.top());
                        tmp.pop();
                    }
                }
            }
        }

        for (auto& s: data) {
            out << s.back();
        }
        out << std::endl;

        for (auto& s: data2) {
            out << s.back();
        }
        out << std::endl;
    }
};

int main(int argc, char **argv) {
    day5 solution{};
    return solution.execute(argc, argv);
}
