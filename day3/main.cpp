#include "solution.h"

class day3 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {

        uint32_t part1_sum{0}, part2_sum{0};

        std::map<char, bool> seen_items;
        int line_index = 0;
        uint64_t badge_masks[3] = {0};

        for (std::string line; std::getline(in, line); line_index++) {
            seen_items.clear();
            for (size_t i = 0; i < line.size() / 2; i++) {
                seen_items[line[i]] = true;
            }
            for (size_t i = line.size() - 1; i >= line.size() / 2; i--) {
                auto c = line[i];
                if (seen_items.contains(c) && seen_items[c]) {
                    part1_sum += priority_for_item(c);
                    seen_items[c] = false;
                }
            }

            auto badge_group_index = line_index % 3;
            for (auto& c: line) {
                badge_masks[badge_group_index] |= 2UL << priority_for_item(c);
            }

            if (badge_group_index == 2) {
                auto badge = badge_masks[0] & badge_masks[1] & badge_masks[2];
                part2_sum += log2(badge >> 1);
                badge_masks[0] = badge_masks[1] = badge_masks[2] = 0;
            }
        }
        out << part1_sum << std::endl;
        out << part2_sum << std::endl;
    }

    static uint32_t priority_for_item(char item) {
        return item >= 'A' && item <= 'Z' ? item - 'A' + 27 : item - 'a' + 1;
    }

};

int main(int argc, char **argv) {
    day3 solution{};
    return solution.execute(argc, argv);
}
