#pragma once

#include "TFunctionFilter.h"
#include "../TColor.h"
#include "../TArgsValidator.h"
#include "../TDefaultArgValidator.h"
#include <memory>

struct TNegativeFilterFunctor {
    void operator()(TColor& pixel) {
        pixel.R = 1 - pixel.R;
        pixel.G = 1 - pixel.G;
        pixel.B = 1 - pixel.B;
    }
};

class TNegativeFilter : public TFunctionFilter<TNegativeFilterFunctor> {
public:
    using ArgsValidator = TArgsValidator<TDefaultArgValidator>;
    static std::unique_ptr<TNegativeFilter> Create(const TArgList&) {
        return std::make_unique<TNegativeFilter>();
    }

    TNegativeFilter() = default;
};
