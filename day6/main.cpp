#include "solution.h"

template<unsigned int N>
struct frame_start_detector {
    bool is_detected() const {
        return detected;
    }

    bool char_ends_frame_start(char c) {
        if (detected) return false;

        offset++;
        for (size_t i = 0; i < buffer_size; i++) {
            if (c == buffer[(read_pointer + i) % N]) {
                read_pointer = (read_pointer + i + 1) % N;
                buffer_size -= i + 1;
                break;
            }
        }

        buffer[write_pointer] = c;
        write_pointer = (write_pointer + 1) % N;
        buffer_size++;
        if (buffer_size == N) {
            detected = true;
            return true;
        }
        return false;
    }

    bool detected = false;
    size_t offset = 0;
    std::array<char, N> buffer;
    uint8_t buffer_size = 0;
    uint8_t read_pointer = 0;
    uint8_t write_pointer = 0;
};

class day6 : public aoc::solution {
protected:

    void run(std::istream& in, std::ostream& out) override {
        frame_start_detector<4> part1_detector{};
        frame_start_detector<14> part2_detector{};

        for (char c; in >> c;) {
            if (!part1_detector.is_detected() && part1_detector.char_ends_frame_start(c)) {
                out << part1_detector.offset << std::endl;
            }

            if (part2_detector.char_ends_frame_start(c)) {
                out << part2_detector.offset << std::endl;
                break;
            }
        }
    }
};

int main(int argc, char **argv) {
    day6 solution{};
    return solution.execute(argc, argv);
}
