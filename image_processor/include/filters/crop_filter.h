#pragma once
#include "filter.h"

class Crop : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char* argv[], int& pos) override;
};