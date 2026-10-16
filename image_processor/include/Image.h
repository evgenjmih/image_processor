#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "BMP.h"

const float EPSILON = 1.0e-3;

struct Color {
    float r{0};
    float g{0};
    float b{0};
};


class Image {
public:
    using Matrix = std::vector<std::vector<Color>>;
    Image(int width, int height);
    ~Image();
    int GetWidth() const;
    int GetHeight() const;
    Color& At(int x, int y);
    const Color& At(int x, int y) const;

    bool operator==(const Image& other) const;

private:
    uint32_t width_;
    uint32_t height_;
    Matrix colors_;
};