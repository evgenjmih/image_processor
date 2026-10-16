#include <iostream>
#include "../include/Image.h"

const int WIDTH = 10;
const int HEIGHT = 20;
const int SMALL_SIZE = 5;
const float PIXEL_R = 1.0f;
const float PIXEL_G = 0.5f;
const float PIXEL_B = 0.0f;

int TestImageCreation() {
    Image img(WIDTH, HEIGHT);
    if (img.GetWidth() != WIDTH || img.GetHeight() != HEIGHT) {
        std::cerr << "Тест создания изображения упал" << std::endl;
        return 1;
    }
    std::cout << "Тест создания изображения пройден" << std::endl;
    return 0;
}

int TestPixelAccess() {
    Image img(SMALL_SIZE, SMALL_SIZE);
    Color c(PIXEL_R, PIXEL_G, PIXEL_B);
    img.At(2, 3) = c;

    Color got = img.At(2, 3);
    if (got.r != PIXEL_R || got.g != PIXEL_G || got.b != PIXEL_B) {
        std::cerr << "Тест пикселей упал" << std::endl;
        return 1;
    }
    std::cout << "Тест пикселей пройден" << std::endl;
    return 0;
}

int main() {
    int failed = 0;
    failed += TestImageCreation();
    failed += TestPixelAccess();

    if (failed == 0) {
        std::cout << "\nВсе тесты пройдены" << std::endl;
        return 0;
    } else {
        std::cout << "\nНеудач: " << failed << std::endl;
        return 1;
    }
}