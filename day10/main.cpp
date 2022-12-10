#include "solution.h"

enum class mnemonic {
    noop,
    addx
};


struct instruction {
    mnemonic opcode;
    int32_t argument;
};

struct cpu {
    int64_t x{1}, old_x{1};
    uint32_t cycle{0};
    instruction executed_instruction;
    size_t instruction_cycles{0};


    bool tick() {
        if (instruction_cycles == 0) return false;

        cycle++;
        old_x = x;
        instruction_cycles--;
        if (instruction_cycles == 0) {
            if (executed_instruction.opcode == mnemonic::addx) {
                x += executed_instruction.argument;
            }
            return false;
        }
        return true;
    }

    void execute(instruction i) {
        executed_instruction = i;
        instruction_cycles = i.opcode == mnemonic::noop ? 1 : 2;
    }

};


class day10 : public aoc::solution {
protected:

    bool time_to_sample_cycle(uint32_t cycle) {
        return cycle == 20 || (cycle > 20 && (cycle - 20) % 40 == 0);
    }

    void run(std::istream& in, std::ostream& out) override {

        std::vector<instruction> program;
        cpu computer;

        bool do_continue;
        int64_t part1{0};
        int64_t x = 0;
        for (std::string line; std::getline(in, line);) {
            auto pieces = aoc::split_string(line, " ");
            auto mnemonic = pieces[0];

            if (pieces[0] == "noop") {
                auto i = instruction{mnemonic::noop};
                program.push_back(i);
                computer.execute(i);
            } else {
                int32_t amount = std::stoi(pieces[1]);
                auto i = instruction{mnemonic::addx, amount};
                program.push_back(i);
                computer.execute(i);
            }

            do {

                out << ((abs(x - computer.x) > 1) ? '.' : '#');
                x++;
                if (x > 39) {
                    x = 0;
                    out << std::endl;
                }
                do_continue = computer.tick();
                if (time_to_sample_cycle(computer.cycle)) {
                    part1 += computer.cycle * computer.old_x;
                }
            } while (do_continue);
        }

        out << part1 << std::endl;
    }
};

int main(int argc, char **argv) {
    day10 solution{};
    return solution.execute(argc, argv);
}
