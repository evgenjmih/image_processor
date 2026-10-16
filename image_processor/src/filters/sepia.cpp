#include "filters/sepia_filter.h"
#include <algorithm>

const float R1 = 0.393f;
const float R2 = 0.769f;
const float R3 = 0.189f;
const float G1 = 0.349f;
const float G2 = 0.686f;
const float G3 = 0.168f;
const float B1 = 0.272f;
const float B2 = 0.534f;
const float B3 = 0.131f;

void Sepia::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            const Color& p = image.At(x, y);

            float r = p.r;
            float g = p.g;
            float b = p.b;
            float new_r = std::min(1.0f, r * R1 + g * R2 + b * R3);
            float new_g = std::min(1.0f, r * G1 + g * G2 + b * G3);
            float new_b = std::min(1.0f, r * B1 + g * B2 + b * B3);

            image.At(x, y) = {new_r, new_g, new_b};
        }
    }
}