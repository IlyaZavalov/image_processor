#pragma once

#include "TFilter.h"
#include "../TArgsValidator.h"
#include "../TDefaultArgValidator.h"
#include <memory>

class TCropFilter : public TFilter {
public:
    using ArgsValidator = TArgsValidator<TDefaultArgValidator, size_t, size_t>;
    static std::unique_ptr<TCropFilter> Create(const TArgList& list);

    TCropFilter(size_t width, size_t height);
    void Apply(TImage& image) override;

private:
    size_t width_;
    size_t height_;
};