#pragma once

#include "TMatrixFilter.h"
#include "../aliases.h"
#include "../TArgsValidator.h"
#include "../TDefaultArgValidator.h"
#include <memory>

class TSharpeningFilter : public TMatrixFilter {
public:
    static constexpr TMatrix MATRIX = {{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}};
    using ArgsValidator = TArgsValidator<TDefaultArgValidator>;
    static std::unique_ptr<TSharpeningFilter> Create(const TArgList&) {
        return std::make_unique<TSharpeningFilter>();
    }

    TSharpeningFilter() : TMatrixFilter(MATRIX) {
    }
};
