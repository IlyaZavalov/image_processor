#pragma once

#include "TMatrixFilter.h"
#include "TGrayscaleFilter.h"
#include "../TArgsValidator.h"
#include "../TDefaultArgValidator.h"

class TEdgeDetectionFilter : public TFilter {
public:
    static constexpr TMatrix MATRIX = {{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}};
    using ArgsValidator = TArgsValidator<TDefaultArgValidator, double>;
    static std::unique_ptr<TEdgeDetectionFilter> Create(TArgList list);

    explicit TEdgeDetectionFilter(double threshold);
    void Apply(TImage& image) override;

private:
    double threshold_;
    TGrayscaleFilter grayscale_filter_;
    TMatrixFilter edge_det_matrix_filter_;
};