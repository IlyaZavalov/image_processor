#pragma once

#include "TFunctionFilter.h"
#include "../TColor.h"
#include "../TArgsValidator.h"
#include "../TDefaultArgValidator.h"
#include <memory>

struct TGrayscaleFilterFunctor {
    void operator()(TColor& pixel) {
        const TColor::ValueType new_value = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
        pixel.R = new_value;
        pixel.G = new_value;
        pixel.B = new_value;
    }
};

class TGrayscaleFilter : public TFunctionFilter<TGrayscaleFilterFunctor> {
public:
    using ArgsValidator = TArgsValidator<TDefaultArgValidator>;
    static std::unique_ptr<TGrayscaleFilter> Create(const TArgList&) {
        return std::make_unique<TGrayscaleFilter>();
    }
};