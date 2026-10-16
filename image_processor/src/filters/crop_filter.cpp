#include "filters/crop_filter.h"
#include <algorithm>

void Crop::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    args = 2;
    IsValid(argc, argv, pos);

    int new_width = std::stoi(argv[pos + 1]);
    int new_height = std::stoi(argv[pos + 2]);

    new_width = std::min(new_width, image.GetWidth());
    new_height = std::min(new_height, image.GetHeight());

    Image new_image(new_width, new_height);

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            new_image.At(x, y) = image.At(x, y);
        }
    }

    image = new_image;
    pos += 2;
}