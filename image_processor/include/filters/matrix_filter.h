#pragma once

class MatrixFilter {
public:
    void Apply(Image& image, const std::vector<std::vector<float>>& m);
};