#pragma once
#include "Image.h"

class Reader {
public:
    static Image Read(std::string_view path);
    Image Read();

private:
    const char* path_;
};
