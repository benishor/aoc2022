#include "solution.h"

struct position {
    union {
        struct {
            int32_t x;
            int32_t y;
        };
        int64_t value;
    };
};

static bool need_to_move_tail(position head, position tail) {
    int32_t dx = abs(head.x - tail.x);
    int32_t dy = abs(head.y - tail.y);
    return dx > 1 || dy > 1;
}

static position resolve_tail_pos(position head, position tail) {
    if (!need_to_move_tail(head, tail)) {
        return tail;
    }


    if (tail.y == head.y) {
        if ((head.x - tail.x) == -2)
            return {.x = static_cast<int32_t>((tail.x - 1)), .y = tail.y};
        else if ((head.x - tail.x) == 2)
            return {.x = static_cast<int32_t>((tail.x + 1)), .y = tail.y};
    }

    if (tail.x == head.x) {
        if ((head.y - tail.y) == -2)
            return {.x = tail.x, .y = static_cast<int32_t>((tail.y - 1))};
        else if ((head.y - tail.y) == 2)
            return {.x = tail.x, .y = static_cast<int32_t>((tail.y + 1))};
    }

    // Otherwise, if the head and tail aren't touching and aren't in the same row or column, the tail always moves one step diagonally to keep up:
    int32_t dx = (head.x - tail.x) / abs(head.x - tail.x);
    int32_t dy = (head.y - tail.y) / abs(head.y - tail.y);
    return {.x = static_cast<int32_t>(tail.x + dx), .y = static_cast<int32_t>(tail.y + dy)};
}


std::ostream& operator<<(std::ostream& out, const position& p) {
    out << "{x:" << p.x << ", y:" << p.y << "}";
    return out;
}


template<int N>
struct game {

    game() {
        seen_positions.insert(positions[1].value);
    }

    void up() {
        positions[0].y++;
        solve();
    }

    void down() {
        positions[0].y--;
        solve();
    }

    void left() {
        positions[0].x--;
        solve();
    }

    void right() {
        positions[0].x++;
        solve();
    }

    void solve() {
        for (int i = 1; i < N; i++) {
            positions[i] = resolve_tail_pos(positions[i - 1], positions[i]);
        }
        seen_positions.insert(positions[N - 1].value);
    }

    size_t result() {
        return seen_positions.size();
    }

    std::array<position, N> positions{};
    std::set<int64_t> seen_positions;
};

class day9 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {

        game<2> part1;
        game<10> part2;


        for (std::string line; std::getline(in, line);) {
            auto pieces = aoc::split_string(line, " ");
            auto direction = pieces[0][0];
            auto amount = std::stol(pieces[1]);

            switch (direction) {
                case 'L':
                    for (int i = 0; i < amount; i++) {
                        part1.left();
                        part2.left();
                    }
                    break;
                case 'R':
                    for (int i = 0; i < amount; i++) {
                        part1.right();
                        part2.right();
                    }
                    break;
                case 'U':
                    for (int i = 0; i < amount; i++) {
                        part1.up();
                        part2.up();
                    }
                    break;
                case 'D':
                    for (int i = 0; i < amount; i++) {
                        part1.down();
                        part2.down();
                    }
                    break;
            }
        }
        out << part1.result() << std::endl;
        out << part2.result() << std::endl;
    }
};

int main(int argc, char **argv) {
    day9 solution{};
    return solution.execute(argc, argv);
}
