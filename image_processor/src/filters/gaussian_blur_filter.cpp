#include "filters/gaussian_blur_filter.h"
#include <cmath>
#include <vector>
#include "filters/matrix_filter.h"

const float TWO = 2.0f;

void GaussianBlur::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    args = 1;
    IsValid(argc, argv, pos);

    float sigma = std::stof(argv[pos + 1]);

    int radius = static_cast<int>(std::ceil(2 * sigma));
    int size = 2 * radius + 1;

    std::vector<float> kernel(size);
    float sum = 0.0f;
    float two_sigma_sq = TWO * sigma * sigma;

    for (int i = -radius; i <= radius; ++i) {
        float value = std::exp(static_cast<float>(-(i * i)) / two_sigma_sq);
        kernel[i + radius] = value;
        sum += value;
    }

    for (int i = 0; i < size; ++i) {
        kernel[i] /= sum;
    }

    MatrixFilter mf;

    std::vector<std::vector<float>> horizontal(1, kernel);
    mf.Apply(image, horizontal);

    std::vector<std::vector<float>> vertical(size);
    for (int i = 0; i < size; ++i) {
        vertical[i] = {kernel[i]};
    }
    mf.Apply(image, vertical);

    pos += 1;
}