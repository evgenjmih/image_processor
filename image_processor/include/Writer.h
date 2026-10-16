#pragma once

class Writer {
public:
    static Image Read(std::string_view path);
    void Export(const Image& image);

private:
    const char* path_;
};
