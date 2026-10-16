#pragma once
#include "filter.h"
#include <cmath>

class Wave : public Filter {
public:
    void ApplyFilter(Image& image, int argc, const char* argv[], int& pos) override;

private:
    int amplitude_;
    float frequency_;
};