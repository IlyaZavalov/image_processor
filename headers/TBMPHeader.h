#pragma once

#include "THeader.h"

class TBMPHeader : public THeader<uint16_t, uint32_t, uint16_t, uint16_t, uint32_t> {
public:
    enum : size_t { ID_INDEX, FILE_SIZE_INDEX, PIXEL_ARRAY_OFFSET_INDEX = 4 };

    uint16_t& ID() {
        return Get<ID_INDEX>();
    }

    uint32_t& FileSize() {
        return Get<FILE_SIZE_INDEX>();
    }

    uint32_t& PixelArrayOffset() {
        return Get<PIXEL_ARRAY_OFFSET_INDEX>();
    }
};
