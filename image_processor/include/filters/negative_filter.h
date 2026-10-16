#pragma once
#include "filter.h"

class Negative : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char* argv[], int& pos) override;
};