#include "solution.h"

class day8 : public aoc::solution {
protected:

    bool is_tree_visible(std::vector<std::string> forest, size_t row, size_t col) {
        uint8_t tree = forest[row][col];
        bool visible = true;

        // visible from the left ?
        for (size_t x = 0; x < col; x++) {
            if (forest[row][x] >= tree) {
                visible = false;
                break;
            }
        }
        if (visible) return true;

        // visible from the right?
        visible = true;
        for (size_t x = forest[0].size() - 1; x > col; x--) {
            if (forest[row][x] >= tree) {
                visible = false;
                break;
            }
        }
        if (visible) return true;

        // visible from the bottom?
        visible = true;
        for (size_t y = forest.size() - 1; y > row; y--) {
            if (forest[y][col] >= tree) {
                visible = false;
                break;
            }
        }
        if (visible) return true;

        // visible from the top ?
        visible = true;
        for (size_t y = 0; y < row; y++) {
            if (forest[y][col] >= tree) {
                visible = false;
                break;
            }
        }
        return visible;
    }

    size_t scenic_score_for_tree(std::vector<std::string> forest, size_t row, size_t col) {
        size_t score{1};
        uint8_t tree = forest[row][col];

        // looking up
        int dir_score = 0;
        for (int y = row - 1; y >= 0; y--) {
            dir_score++;
            if (forest[y][col] >= tree) break;
        }
        score *= dir_score;

        // looking down
        dir_score = 0;
        for (int y = row + 1; y < forest.size(); y++) {
            dir_score++;
            if (forest[y][col] >= tree) break;
        }
        score *= dir_score;

        // looking left
        dir_score = 0;
        for (int x = col - 1; x >= 0; x--) {
            dir_score++;
            if (forest[row][x] >= tree) break;
        }
        score *= dir_score;

        // looking right
        dir_score = 0;
        for (int x = col + 1; x < forest[0].size(); x++) {
            dir_score++;
            if (forest[row][x] >= tree) break;
        }
        score *= dir_score;

        return score;
    }

    void run(std::istream& in, std::ostream& out) override {
        std::vector<std::string> data;
        for (std::string line; std::getline(in, line);) {
            data.push_back(line);
        }
        size_t columns = data[0].size();
        size_t rows = data.size();

        size_t part1 = 2 * rows + 2 * columns - 4;
        size_t part2 = 0;
        for (size_t row = 1; row < rows - 1; row++) {
            for (size_t col = 1; col < columns - 1; col++) {
                part1 += is_tree_visible(data, row, col);
                auto scenic_score = scenic_score_for_tree(data, row, col);
                part2 = std::max(part2, scenic_score);
            }
        }
        out << part1 << std::endl;
        out << part2 << std::endl;
    }
};

int main(int argc, char **argv) {
    day8 solution{};
    return solution.execute(argc, argv);
}
