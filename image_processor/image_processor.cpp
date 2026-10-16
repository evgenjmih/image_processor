#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Reader.h"
#include "Writer.h"
#include "filters/filter.h"
#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/sepia_filter.h"
#include "filters/wave_filter.h"

std::unique_ptr<Filter> CreateFilter(const std::string& name, const std::vector<std::string>& args, int argc,
                                     const char* argv[], int& pos) {
    if (name == "-crop") {
        if (args.size() < 2) {
            throw std::invalid_argument("Недостаточно аргументов");
        }
        auto filter = std::make_unique<Crop>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-gs") {
        auto filter = std::make_unique<GrayScale>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-neg") {
        auto filter = std::make_unique<Negative>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-sharp") {
        auto filter = std::make_unique<Sharpening>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-edge") {
        if (args.empty()) {
            throw std::invalid_argument("Недостаточно аргументов");
        }
        auto filter = std::make_unique<EdgeDetection>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-blur") {
        if (args.empty()) {
            throw std::invalid_argument("Недостаточно аргументов");
        }
        auto filter = std::make_unique<GaussianBlur>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-sepia") {
        auto filter = std::make_unique<Sepia>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    if (name == "-wave") {
        if (args.size() < 2) {
            throw std::invalid_argument("Недостаточно аргументов");
        }
        auto filter = std::make_unique<Wave>();
        filter->IsValid(argc, argv, pos);
        return filter;
    }
    throw std::invalid_argument("Неизвестный фильтр: " + name);
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            throw std::invalid_argument("Недостаточно аргументов");
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];

        Reader reader(input_file);
        Image image = reader.Read();

        int pos = 3;
        std::vector<std::unique_ptr<Filter>> filters;

        while (pos < argc) {
            std::string filter_name = argv[pos];
            std::vector<std::string> filter_args;

            int current_pos = pos;

            int next_pos = pos + 1;
            while (next_pos < argc && argv[next_pos][0] != '-') {
                filter_args.push_back(argv[next_pos]);
                ++next_pos;
            }

            auto filter = CreateFilter(filter_name, filter_args, argc, const_cast<const char**>(argv), current_pos);

            filter->ApplyFilter(image, argc, const_cast<const char**>(argv), current_pos);

            filters.push_back(std::move(filter));
            pos = next_pos;
        }

        Writer writer(output_file);
        writer.Export(image);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}