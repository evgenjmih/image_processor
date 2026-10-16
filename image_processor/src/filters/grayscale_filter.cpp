#include "filters/grayscale_filter.h"

const float GRAY_R = 0.299f;
const float GRAY_G = 0.587f;
const float GRAY_B = 0.114f;

void GrayScale::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            const Color& pixel = image.At(x, y);
            float gray = GRAY_R * pixel.r + GRAY_G * pixel.g + GRAY_B * pixel.b;
            image.At(x, y) = {gray, gray, gray};
        }
    }
}