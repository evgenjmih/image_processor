#include "Image.h"

Image::Image(int width, int height)
    : width_(width), height_(height), colors_(Matrix(height, std::vector<Color>(width))) {
}

Image::~Image() = default;

bool Image::operator==(const Image &other) const {
    if (height_ != other.height_ || width_ != other.width_) {
        return false;
    }
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (!(At(x, y) == other.At(x, y))) {
                return false;
            }
        }
    }
    return true;
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

Color &Image::At(int x, int y) {
    x = std::min(std::max(x, 0), width_ - 1);
    y = std::min(std::max(y, 0), height_ - 1);
    return colors_[y][x];
}

const Color &Image::At(int x, int y) const {
    x = std::min(std::max(x, 0), width_ - 1);
    y = std::min(std::max(y, 0), height_ - 1);
    return colors_[y][x];
}
