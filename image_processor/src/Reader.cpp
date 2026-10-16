#include "Reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

const int BYTE = 8;
const float COLOR_SCALE = 255.0f;

template <typename T>
void ReadValue(std::ifstream &input, T &value) {
    std::make_unsigned_t<T> x = 0;
    unsigned char buffer[sizeof(value)];
    input.read(reinterpret_cast<char *>(buffer), sizeof(value));
    for (size_t i = 0; i < sizeof(value); ++i) {
        x += buffer[i] << (BYTE * i);
    }
    value = static_cast<T>(x);
}

Reader::Reader(const char *path) : path_(path) {
}

Image Reader::Read() {
    std::ifstream input(path_, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error{"error opening file"};
    }

    BMP header;
    ReadValue(input, header.file_header.file_type);
    if (header.file_header.file_type != BMP_TYPE) {
        throw std::runtime_error{"not a bmp"};
    }

    ReadValue(input, header.file_header.file_size);
    ReadValue(input, header.file_header.reserved1);
    ReadValue(input, header.file_header.reserved2);
    ReadValue(input, header.file_header.offset_data);

    ReadValue(input, header.info_header.size);
    ReadValue(input, header.info_header.width);
    ReadValue(input, header.info_header.height);
    ReadValue(input, header.info_header.planes);
    ReadValue(input, header.info_header.bit_count);
    ReadValue(input, header.info_header.compression);
    ReadValue(input, header.info_header.size_image);
    ReadValue(input, header.info_header.x_pixels_per_meter);
    ReadValue(input, header.info_header.y_pixels_per_meter);
    ReadValue(input, header.info_header.colors_used);
    ReadValue(input, header.info_header.colors_important);

    int32_t width = header.info_header.width;
    int32_t height = std::abs(header.info_header.height);
    bool top_down = header.info_header.height < 0;

    int padding_amount = (4 - (width * 3) % 4) % 4;

    Image image(width, height);

    for (int y = 0; y < height; ++y) {
        int image_y = top_down ? y : (height - 1 - y);

        for (int x = 0; x < width; ++x) {
            unsigned char color[3] = {0, 0, 0};
            input.read(reinterpret_cast<char *>(color), 3);

            if (input.gcount() != 3) {
                throw std::runtime_error("Чето не то");
            }

            float r = static_cast<float>(color[2]) / COLOR_SCALE;
            float g = static_cast<float>(color[1]) / COLOR_SCALE;
            float b = static_cast<float>(color[0]) / COLOR_SCALE;

            image.At(x, image_y) = {r, g, b};
        }

        if (padding_amount > 0) {
            input.ignore(padding_amount);
        }
    }

    return image;
}