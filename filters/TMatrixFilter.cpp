#include "TMatrixFilter.h"

TMatrixFilter::TMatrixFilter(const TMatrix& matrix) : matrix_(matrix) {
}

TMatrixFilter::TMatrixFilter(TMatrix&& matrix) : matrix_(std::move(matrix)) {
}

void TMatrixFilter::Apply(TImage& image) {
    ApplyMatrix(image, matrix_);
}

void TMatrixFilter::ApplyMatrix(TImage& image, const TMatrix& matrix) {
    if (image.Height() == 0 || image.Width() == 0) {
        return;
    }

    std::array<std::vector<TColor>, 3> saved_rows = {image[0], image[0], image[std::min(1ul, image.Height())]};

    const auto set_new_color = [&image, &matrix, &saved_rows](size_t x, size_t y) {
        TColor& processed_pixel = image[x][y];
        processed_pixel = TColor();

        const auto get_limited = [](auto val, auto min_val, auto max_val) {
            return std::max(min_val, std::min(max_val, val));
        };
        const auto limit_value = [&get_limited](auto& val, auto min_val, auto max_val) {
            val = get_limited(val, min_val, max_val);
        };

        for (size_t mx = 0; mx < matrix.size(); ++mx) {
            for (size_t my = 0; my < matrix[mx].size(); ++my) {
                const size_t cur_y = get_limited(static_cast<ssize_t>(y + my) - 1, static_cast<ssize_t>(0),
                                                 static_cast<ssize_t>(image.Width()) - 1);
                processed_pixel.AddPixelMultipliedBy(saved_rows[mx][cur_y], matrix[mx][my]);
            }
        }

        const auto limit_color_value = [&limit_value](TColor::ValueType& x) { limit_value(x, 0., 1.); };

        limit_color_value(processed_pixel.R);
        limit_color_value(processed_pixel.G);
        limit_color_value(processed_pixel.B);
    };

    for (size_t x = 0; x < image.Height(); ++x) {
        for (size_t y = 0; y < image.Width(); ++y) {
            set_new_color(x, y);
        }
        std::swap(saved_rows[0], saved_rows[1]);
        std::swap(saved_rows[1], saved_rows[2]);
        if (x + 2 < image.Height()) {
            saved_rows[2] = image[x + 2];
        } else {
            saved_rows[2] = saved_rows[1];
        }
    }
}
