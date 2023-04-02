#include "TBlurFilter.h"

#include "../Colors.h"
#include <cmath>
#include <charconv>

TBlurFilter::TBlurFilter(TColor::ValueType sigma) : sigma_(sigma) {
}

void TBlurFilter::Apply(TImage& image) {
    const size_t coefficients_count = static_cast<size_t>(3 * ceil(sigma_) + 1);
    const std::vector<TColor::ValueType> coefficients = GetCoefficients(coefficients_count);

    for (size_t x = 0; x < image.Height(); ++x) {
        const std::vector<TColor> copied_row = image.CopyRow(x);
        for (size_t y = 0; y < image.Width(); ++y) {
            TColor& processed_pixel = image[x][y];
            processed_pixel = color::BLACK;
            processed_pixel.AddPixelMultipliedBy(copied_row[y], coefficients[0]);
            for (size_t i = 1; i < coefficients_count; ++i) {
                processed_pixel.AddPixelMultipliedBy(copied_row[std::max(0l, static_cast<ssize_t>(y - i))],
                                                     coefficients[i]);
                processed_pixel.AddPixelMultipliedBy(copied_row[std::min(image.Width() - 1, y + i)], coefficients[i]);
            }
        }
    }

    for (size_t y = 0; y < image.Width(); ++y) {
        const std::vector<TColor> copied_column = image.CopyColumn(y);
        for (size_t x = 0; x < image.Height(); ++x) {
            TColor& processed_pixel = image[x][y];
            processed_pixel = color::BLACK;
            processed_pixel.AddPixelMultipliedBy(copied_column[x], coefficients[0]);
            for (size_t i = 1; i < coefficients_count; ++i) {
                processed_pixel.AddPixelMultipliedBy(copied_column[std::max(0l, static_cast<ssize_t>(x - i))],
                                                     coefficients[i]);
                processed_pixel.AddPixelMultipliedBy(copied_column[std::min(image.Height() - 1, x + i)],
                                                     coefficients[i]);
            }
        }
    }
}

std::unique_ptr<TBlurFilter> TBlurFilter::Create(const TArgList& list) {
    double sigma = 0;
    std::from_chars(list[0].begin(), list[0].end(), sigma);
    return std::make_unique<TBlurFilter>(sigma);
}

std::vector<TColor::ValueType> TBlurFilter::GetCoefficients(size_t cnt) const {
    const auto sqr = [](auto val) { return val * val; };
    const TColor::ValueType double_squared_sigma = 2 * sqr(sigma_);
    const TColor::ValueType sqrt_coefficient = sqrt(std::numbers::pi * double_squared_sigma);
    std::vector<TColor::ValueType> coefficients;
    coefficients.reserve(cnt);
    for (size_t i = 0; i < cnt; ++i) {
        double val = exp(-(sqr(static_cast<double>(i))) / double_squared_sigma) / sqrt_coefficient;
        coefficients.push_back(val);
    }
    return coefficients;
}

template <>
bool TBlurFilter::ArgValidator::Validate<double>(TArgType arg) {
    std::stringstream ss;
    double double_arg = 0;
    ss << arg;
    ss >> double_arg;
    return ss.eof() && !ss.fail() && double_arg > 0;
}
