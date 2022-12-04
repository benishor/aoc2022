#include "solution.h"

class day5 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        uint32_t part1{0}, part2{0};

        auto range_re = std::regex(R"(^(\d+)-(\d+),(\d+)-(\d+)$)");
        for (std::string line; std::getline(in, line);) {

            std::smatch sm{};
            if (std::regex_match(line, sm, range_re)) {
                auto a = std::stol(sm.str(1));
                auto b = std::stol(sm.str(2));
                auto c = std::stol(sm.str(3));
                auto d = std::stol(sm.str(4));

                bool is_containment = ((a <= c && b >= d) || (c <= a && d >= b));
                bool is_overlap = (a <= c && b >= c) || (c <= a && d >= a);
                part1 += is_containment;
                part2 += is_containment | is_overlap;
            } else {
                std::cerr << "Failed to regex match line [" << line << "]" << std::endl;
                exit(1);
            }
        }
        out << part1 << std::endl;
        out << part2 << std::endl;
    }
};

int main(int argc, char **argv) {
    day5 solution{};
    return solution.execute(argc, argv);
}
