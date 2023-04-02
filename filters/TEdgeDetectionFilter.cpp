#include "TEdgeDetectionFilter.h"

#include <charconv>
#include "../Colors.h"

std::unique_ptr<TEdgeDetectionFilter> TEdgeDetectionFilter::Create(TArgList list) {
    double threshold = 0;
    std::from_chars(list[0].begin(), list[0].end(), threshold);
    return std::make_unique<TEdgeDetectionFilter>(threshold);
}

TEdgeDetectionFilter::TEdgeDetectionFilter(double threshold) : threshold_(threshold), edge_det_matrix_filter_(MATRIX) {
}

void TEdgeDetectionFilter::Apply(TImage& image) {
    grayscale_filter_.Apply(image);
    edge_det_matrix_filter_.Apply(image);
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            image[i][j] = (image[i][j].R > threshold_) ? color::WHITE : color::BLACK;
        }
    }
}
