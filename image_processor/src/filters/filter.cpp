#include "filters/filter.h"

void Filter::IsValid(int argc, const char* argv[], int& pos) {
    if (pos + args >= argc) {
        throw std::runtime_error("недостаточно аргументов");
    }

    for (int i = 1; i <= args; ++i) {
        char* endptr = nullptr;
        std::strtof(argv[pos + i], &endptr);
        if (*endptr != '\0') {
            throw std::runtime_error("некорректные аргументы");
        }
    }
}