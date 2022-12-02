#include "solution.h"

class day2 : public aoc::solution {
protected:
    enum element {
        rock = 0,
        paper = 1,
        scissors = 2
    };

    enum outcome {
        lose = 0,
        draw = 1,
        win = 2
    };

    void run(std::istream& in, std::ostream& out) override {
        uint64_t running_score_part_1{0}, running_score_part_2{0};
        for (std::string line; std::getline(in, line);) {
            auto his_move = static_cast<element>(line[0] - 'A');
            auto my_move = static_cast<element>(line[2] - 'X');
            running_score_part_1 += score_round(his_move, my_move);

            auto needed_outcome = static_cast<outcome>(line[2] - 'X');
            my_move = move_for_outcome(his_move, needed_outcome);
            running_score_part_2 += score_round(his_move, my_move);
        }
        out << running_score_part_1 << std::endl;
        out << running_score_part_2 << std::endl;
    }

    static uint64_t score_round(element his, element mine) {
        auto element_score = mine + 1;

        auto did_i_win = mine == (his + 1) % 3;
        auto is_it_draw = mine == his;
        auto outcome_score = did_i_win ? 6 : (is_it_draw ? 3 : 0);

        return element_score + outcome_score;
    }

    static element move_for_outcome(element his, outcome needed_outcome) {
        if (needed_outcome == lose)
            return static_cast<element>(his > 0 ? his - 1 : 2);
        else if (needed_outcome == win)
            return static_cast<element>(his < 2 ? his + 1 : 0);
        else
            return his;
    }
};

int main(int argc, char **argv) {
    day2 solution{};
    return solution.execute(argc, argv);
}
