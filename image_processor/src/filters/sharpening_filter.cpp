#include "filters/sharpening_filter.h"
#include "filters/matrix_filter.h"

const int SHARPEN_CENTER = 5;

void Sharpening::ApplyFilter(Image& image, int argc, const char* argv[], int& pos) {
    MatrixFilter mf;
    mf.Apply(image, {{0, -1, 0}, {-1, SHARPEN_CENTER, -1}, {0, -1, 0}});
}