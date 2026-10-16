#include "filters/wave_filter.h"
#include <cmath>
#include <algorithm>

void Wave::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    args = 2;
    IsValid(argc, argv, pos);

    amplitude_ = std::stoi(argv[pos + 1]);
    frequency_ = std::stof(argv[pos + 2]);

    int width = image.GetWidth();
    int height = image.GetHeight();
    int center_x = width / 2;
    int center_y = height / 2;

    Image new_image(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float dx = static_cast<float>(x - center_x);
            float dy = static_cast<float>(y - center_y);
            float distance = std::sqrt(dx * dx + dy * dy);

            float offset_float = static_cast<float>(amplitude_) * std::sin(frequency_ * distance);
            float angle = std::atan2(dy, dx);

            float src_x_float = static_cast<float>(center_x) + (distance - offset_float) * std::cos(angle);
            float src_y_float = static_cast<float>(center_y) + (distance - offset_float) * std::sin(angle);

            int src_x = static_cast<int>(src_x_float);
            int src_y = static_cast<int>(src_y_float);

            src_x = std::clamp(src_x, 0, width - 1);
            src_y = std::clamp(src_y, 0, height - 1);

            new_image.At(x, y) = image.At(src_x, src_y);
        }
    }

    image = new_image;
    pos += 2;
}