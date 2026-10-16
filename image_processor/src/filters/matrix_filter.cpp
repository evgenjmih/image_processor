#include "filters/matrix_filter.h"

void MatrixFilter::Apply(Image& image, const std::vector<std::vector<float>>& m) {
    Image new_image(image.GetWidth(), image.GetHeight());
    int step_x = static_cast<int>(m.at(0).size() / 2);
    int step_y = static_cast<int>(m.size() / 2);
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            float rr = 0;
            float gg = 0;
            float bb = 0;
            for (size_t i = 0; i < m.size(); ++i) {
                for (size_t j = 0; j < m.at(0).size(); ++j) {
                    int ix = x - step_x + static_cast<int>(j);
                    int iy = y - step_y + static_cast<int>(i);
                    rr += m[i][j] * image.At(ix, iy).r;
                    gg += m[i][j] * image.At(ix, iy).g;
                    bb += m[i][j] * image.At(ix, iy).b;
                }
            }
            rr = std::min(std::max(rr, 0.0f), 1.0f);
            gg = std::min(std::max(gg, 0.0f), 1.0f);
            bb = std::min(std::max(bb, 0.0f), 1.0f);
            new_image.At(x, y) = {rr, gg, bb};
        }
    }
    image = std::move(new_image);
}