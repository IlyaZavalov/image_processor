#include "TCropFilter.h"
#include <charconv>

TCropFilter::TCropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

void TCropFilter::Apply(TImage& image) {
    if (height_ < image.Height()) {
        image.ChangeHeight(height_);
    }
    if (width_ < image.Width()) {
        image.ChangeWidth(width_);
    }
}

std::unique_ptr<TCropFilter> TCropFilter::Create(const TArgList& list) {
    auto to_size_t = [](std::string_view sv) {
        size_t res = 0;
        std::from_chars(sv.begin(), sv.end(), res);
        return res;
    };
    return std::make_unique<TCropFilter>(to_size_t(list[0]), to_size_t(list[1]));
}
