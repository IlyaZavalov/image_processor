#pragma once

#include "../aliases.h"
#include "TFilter.h"

class TMatrixFilter : public TFilter {
public:
    explicit TMatrixFilter(const TMatrix& matrix);
    explicit TMatrixFilter(TMatrix&& matrix);
    void Apply(TImage& image) override;

private:
    TMatrix matrix_;

    static void ApplyMatrix(TImage& image, const TMatrix& matrix);
};
