#include "TArgParser.h"
#include "TImage.h"
#include "filters/all_filters.h"
#include <iostream>
#include <fstream>

const std::unordered_map<std::string_view, TFilterInfo> SUPPORTED_FILTERS{
        {"crop", GetFilterInfo<TCropFilter>()},          {"gs", GetFilterInfo<TGrayscaleFilter>()},
        {"neg", GetFilterInfo<TNegativeFilter>()},       {"sharp", GetFilterInfo<TSharpeningFilter>()},
        {"edge", GetFilterInfo<TEdgeDetectionFilter>()}, {"blur", GetFilterInfo<TBlurFilter>()}};

const std::string HELP =
        "image_processor\n"
        "requirements for image:\n"
        "-bmp file format\n"
        "-24 bits per pixel\n"
        "-no compression\n"
        "-BITMAPINFOHEADER DIB header\n"
        "Usage: ./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n\n"
        "Available filters:\n"
        "-crop width height\n"
        "Crop the image to the specified width and height. The top left of the image is used.\n"
        "If the requested width or height exceeds the dimensions of the original image, the available part of the image is "
        "returned.\n\n"
        "-gs\n"
        "Converts an image to grayscale.\n\n"
        "-neg\n"
        "Converts an image to negative.\n\n"
        "-sharp\n"
        "Sharpening.\n\n"
        "-edge\n"
        "Edge detection. Pixels with a value more than threshold are painted white, the others are painted black.\n\n"
        "-blur sigma\n"
        "Gaussian blur with parameter sigma.\n";

int main(int argc, char** argv) {
    TFilterManager manager(SUPPORTED_FILTERS);
    TArgParser parser(manager);
    TArgParser::TParsed parsed = parser.Parse(argc, argv);

    if (parsed.need_help) {
        std::cout << HELP;
        return 1;
    }

    TImage image;

    try {
        std::ifstream file_in(parsed.input_file_path.data());
        if (!file_in.is_open()) {
            std::cout << "loading error : opening input file failed" << std::endl;
            return 1;
        }
        image.Load(file_in);
        file_in.close();
    } catch (std::exception& exception) {
        std::cout << "loading error : " << exception.what() << std::endl;
        return 1;
    }

    try {
        manager.AddFilters(parsed.filters);
        manager.ApplyFilters(image);
    } catch (std::exception& exception) {
        std::cout << "applying error : " << exception.what() << std::endl;
        return 1;
    }

    try {
        std::ofstream file_out(parsed.output_file_path.data());
        image.Write(file_out);
        file_out.close();
    } catch (std::exception& exception) {
        std::cout << "writing error : " << exception.what() << std::endl;
        return 1;
    }

    std::cout << "successful" << std::endl;

    return 0;
}