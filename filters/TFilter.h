#pragma once

#include "../aliases.h"
#include "../TImage.h"

class TFilter {
public:
    virtual void Apply(TImage& image) = 0;
    virtual ~TFilter() = default;
};
