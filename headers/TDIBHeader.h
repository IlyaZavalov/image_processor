#pragma once

#include "THeader.h"

class TDIBHeader : public THeader<uint32_t, uint32_t, int32_t, uint16_t, uint16_t, uint32_t, uint32_t, uint32_t,
                                  uint32_t, uint32_t, uint32_t> {
public:
    enum : size_t {
        HEADER_SIZE_INDEX,
        WIDTH_INDEX,
        HEIGHT_INDEX,
        PLANES_INDEX,
        BITS_PER_PIXEL_INDEX,
        COMPRESSION_INDEX,
        PIXEL_ARRAY_SIZE_INDEX,
        PIXEL_PER_METRE_X_INDEX,
        PIXEL_PER_METRE_Y_INDEX,
        COLORS_IN_PALETTE_INDEX,
        IMPORTANT_COLORS_INDEX
    };

    uint32_t& HeaderSize() {
        return Get<HEADER_SIZE_INDEX>();
    }

    uint32_t& Width() {
        return Get<WIDTH_INDEX>();
    }

    int32_t& Height() {
        return Get<HEIGHT_INDEX>();
    }

    uint32_t Width() const {
        return Get<WIDTH_INDEX>();
    }

    int32_t Height() const {
        return Get<HEIGHT_INDEX>();
    }

    uint16_t& Planes() {
        return Get<PLANES_INDEX>();
    }

    uint16_t& BitsPerPixel() {
        return Get<BITS_PER_PIXEL_INDEX>();
    }

    uint32_t& Compression() {
        return Get<COMPRESSION_INDEX>();
    }

    uint32_t& PixelArraySize() {
        return Get<PIXEL_ARRAY_SIZE_INDEX>();
    }

    uint32_t& PixelsPerMetreX() {
        return Get<PIXEL_PER_METRE_X_INDEX>();
    }

    uint32_t& PixelsPerMetreY() {
        return Get<PIXEL_PER_METRE_Y_INDEX>();
    }

    uint32_t& ColorsInPalette() {
        return Get<COLORS_IN_PALETTE_INDEX>();
    }

    uint32_t& ImportantColors() {
        return Get<IMPORTANT_COLORS_INDEX>();
    }
};
