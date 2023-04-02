#pragma once

#include "TFilter.h"
#include "../TArgsValidator.h"
#include <memory>

class TBlurFilter : public TFilter {
public:
    struct ArgValidator {
        template <typename T>
        static bool Validate(TArgType type);
    };
    using ArgsValidator = TArgsValidator<ArgValidator, double>;
    static std::unique_ptr<TBlurFilter> Create(const TArgList& list);

    explicit TBlurFilter(TColor::ValueType sigma);
    void Apply(TImage& image) override;

private:
    TColor::ValueType sigma_;

    std::vector<TColor::ValueType> GetCoefficients(size_t cnt) const;
};
