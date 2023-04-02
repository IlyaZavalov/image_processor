#pragma once

#include "TFilter.h"

template <typename TFunc>
class TFunctionFilter : public TFilter {
public:
    void Apply(TImage& image) override {
        for (size_t i = 0; i < image.Height(); ++i) {
            std::for_each(image[i].begin(), image[i].end(), func_);
        }
    }

private:
    TFunc func_;
};
