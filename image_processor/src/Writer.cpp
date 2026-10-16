#include <fstream>
#include <iostream>
#include "Writer.h"
#include <cstring>

const int BYTE = 8;
const float COLOR_SCALE = 255.0f;

template <typename T>
void WriteValue(std::ofstream &output, T value) {
    unsigned char buffer[sizeof(value)];
    std::make_unsigned_t<T> x = value;
    for (size_t i = 0; i < sizeof(value); ++i) {
        buffer[i] = x >> (BYTE * i);
    }
    output.write(reinterpret_cast<char *>(buffer), sizeof(value));
}

Writer::Writer(const char *path) : path_(path) {
}

void Writer::Export(const Image &image) {
    std::ofstream output(path_, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }

    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();

    int padding_amount = (4 - (width * 3) % 4) % 4;

    const int file_header_size = 14;
    const int info_header_size = 40;

    uint32_t image_size = (width * 3 + padding_amount) * height;
    uint32_t file_size = file_header_size + info_header_size + image_size;

    WriteValue(output, static_cast<uint16_t>(BMP_TYPE));
    WriteValue(output, file_size);
    WriteValue(output, static_cast<uint16_t>(0));
    WriteValue(output, static_cast<uint16_t>(0));
    WriteValue(output, static_cast<uint32_t>(file_header_size + info_header_size));

    WriteValue(output, static_cast<uint32_t>(info_header_size));
    WriteValue(output, width);
    WriteValue(output, height);
    WriteValue(output, static_cast<uint16_t>(1));
    WriteValue(output, static_cast<uint16_t>(BMP_BIT_COUNT));
    WriteValue(output, static_cast<uint32_t>(0));
    WriteValue(output, image_size);
    WriteValue(output, static_cast<int32_t>(0));
    WriteValue(output, static_cast<int32_t>(0));
    WriteValue(output, static_cast<uint32_t>(0));
    WriteValue(output, static_cast<uint32_t>(0));

    char padding[3] = {0, 0, 0};

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            const Color &pixel = image.At(x, y);

            unsigned char r = static_cast<unsigned char>(pixel.r * COLOR_SCALE);
            unsigned char g = static_cast<unsigned char>(pixel.g * COLOR_SCALE);
            unsigned char b = static_cast<unsigned char>(pixel.b * COLOR_SCALE);

            unsigned char color[] = {b, g, r};
            output.write(reinterpret_cast<char *>(color), 3);
        }

        if (padding_amount > 0) {
            output.write(padding, padding_amount);
        }
    }

    if (!output.good()) {
        throw std::runtime_error("Error writing to file");
    }

    output.close();
}