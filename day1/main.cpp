#include "solution.h"

class day1 : public aoc::solution {
public:

    void run(std::istream& in, std::ostream& out) override {
        uint32_t max_calories[3] = {0};
        uint32_t current_calories = 0;
        for (;;) {
            std::string line;
            bool file_done = !std::getline(in, line);
            if (file_done || line.empty()) {
                for (auto i = 0; i < 3; i++) {
                    if (current_calories > max_calories[i]) {
                        for (auto j = 2; j >= i; j--) {
                            max_calories[j] = max_calories[j - 1];
                        }
                        max_calories[i] = current_calories;
                        break;
                    }
                }
                current_calories = 0;
            } else {
                current_calories += std::stoul(line);
            }
            if (file_done) break;
        }

        out << max_calories[0] << std::endl;
        out << (max_calories[0] + max_calories[1] + max_calories[2]) << std::endl;
    }
};

int main(int argc, char *argv[]) {
    day1 solution;
    return solution.execute(argc, argv);
}