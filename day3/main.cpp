#include "solution.h"

class day3 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        uint64_t part1_sum{0}, part2_sum{0};
        uint64_t group_badges[3] = {0};
        std::string line;

        for (int line_index = 0; std::getline(in, line); line_index++) {
            uint64_t badge_half_1{0};
            uint64_t badge_half_2{0};

            for (size_t i = 0; i < line.size(); i++) {
                auto item_priority = priority_for_item(line[i]);
                auto bit_to_set = 2UL << (item_priority - 1);

                if (i >= line.size() / 2) {
                    badge_half_2 |= bit_to_set;
                } else {
                    badge_half_1 |= bit_to_set;
                }
            }
            part1_sum += log2(badge_half_1 & badge_half_2);

            auto badge_group_index = line_index % 3;
            group_badges[badge_group_index] = badge_half_1 | badge_half_2;
            if (badge_group_index == 2) {
                part2_sum += log2(group_badges[0] & group_badges[1] & group_badges[2]);
                group_badges[0] = group_badges[1] = group_badges[2] = 0;
            }
        }
        out << part1_sum << std::endl;
        out << part2_sum << std::endl;
    }

    static uint64_t priority_for_item(char item) {
        return item >= 'A' && item <= 'Z' ? item - 'A' + 27 : item - 'a' + 1;
    }
};

int main(int argc, char **argv) {
    day3 solution{};
    return solution.execute(argc, argv);
}
