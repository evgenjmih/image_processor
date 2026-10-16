#pragma once
#include "filter.h"

class EdgeDetection : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char* argv[], int& pos) override;
};