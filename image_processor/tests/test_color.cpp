#include <iostream>
#include "../include/Image.h"

const float COLOR_R = 0.5f;
const float COLOR_G = 0.6f;
const float COLOR_B = 0.7f;
const float COLOR_DIFF_R = 0.1f;
const float COLOR_DIFF_G = 0.2f;
const float COLOR_DIFF_B = 0.3f;

int TestColorCreation() {
    Color c(COLOR_R, COLOR_G, COLOR_B);
    if (c.r != COLOR_R || c.g != COLOR_G || c.b != COLOR_B) {
        std::cerr << "Тест создания цвета упал" << std::endl;
        return 1;
    }
    std::cout << "Тест создания цвета пройден" << std::endl;
    return 0;
}

int TestColorEquality() {
    Color a(COLOR_R, COLOR_G, COLOR_B);
    Color b(COLOR_R, COLOR_G, COLOR_B);
    Color c(COLOR_DIFF_R, COLOR_DIFF_G, COLOR_DIFF_B);

    if (!(a == b)) {
        std::cerr << "класс Color неправильно реализует сравнение одинаковых" << std::endl;
        return 1;
    }
    if (a == c) {
        std::cerr << "класс Color неправильно реализует сравнение разных" << std::endl;
        return 1;
    }
    std::cout << "Тест сравнения цветов пройден" << std::endl;
    return 0;
}

int main() {
    int failed = 0;
    failed += TestColorCreation();
    failed += TestColorEquality();

    if (failed == 0) {
        std::cout << "\nВсе тесты пройдены" << std::endl;
        return 0;
    } else {
        std::cout << "\nНеудач: " << failed << std::endl;
        return 1;
    }
}