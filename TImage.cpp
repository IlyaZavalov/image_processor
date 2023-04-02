#include "TImage.h"

TImage::TImage(const TImage& other) {
    *this = other;
}

TImage::TImage(TImage&& other) {
    *this = std::move(other);
}

TImage::TImage(TBMPHeader bmp_header, TDIBHeader dib_header, const PixelArray& pixel_array)
    : bmp_header_(bmp_header), dib_header_(dib_header), pixel_array_(pixel_array) {
}

TImage::TImage(TBMPHeader bmp_header, TDIBHeader dib_header, PixelArray&& pixel_array)
    : bmp_header_(bmp_header), dib_header_(dib_header), pixel_array_(std::move(pixel_array)) {
}

std::vector<TColor>& TImage::operator[](size_t index) {
    return pixel_array_[index];
}

const std::vector<TColor>& TImage::operator[](size_t index) const {
    return pixel_array_[index];
}

TImage& TImage::operator=(const TImage& rhs) {
    bmp_header_ = rhs.bmp_header_;
    dib_header_ = rhs.dib_header_;
    pixel_array_ = rhs.pixel_array_;
    return *this;
}

TImage& TImage::operator=(TImage&& rhs) {
    bmp_header_ = std::move(rhs.bmp_header_);
    dib_header_ = std::move(rhs.dib_header_);
    pixel_array_ = std::move(rhs.pixel_array_);
    return *this;
}

void TImage::Load(std::istream& stream) {
    const uint32_t bitmapinfoheader_pixel_array_offset = 54;
    const uint32_t bitmapinfoheader_dib_header_size = 40;
    const uint32_t supported_bpp = 24;

    bmp_header_.Load(stream);
    if (bmp_header_.PixelArrayOffset() != bitmapinfoheader_pixel_array_offset) {
        throw BadHeaderException();
    }

    dib_header_.Load(stream);
    if (dib_header_.HeaderSize() != bitmapinfoheader_dib_header_size) {
        throw BadHeaderException();
    }

    if (dib_header_.BitsPerPixel() != supported_bpp) {
        throw std::invalid_argument("only 24 bits per pixel format is supported");
    }

    pixel_array_.clear();
    pixel_array_.shrink_to_fit();
    pixel_array_.resize(abs(dib_header_.Height()));
    const auto padding = static_cast<std::streamsize>(dib_header_.Width() % 4);

    const auto load_row = [this, &stream, padding](std::vector<TColor>& pixel_row) {
        pixel_row.reserve(dib_header_.Width());
        for (uint32_t i = 0; i < dib_header_.Width(); ++i) {
            TColor current_pixel;
            current_pixel.Load(stream);
            pixel_row.push_back(current_pixel);
        }
        stream.ignore(padding);
    };

    if (dib_header_.Height() < 0) {
        std::for_each(pixel_array_.begin(), pixel_array_.end(), load_row);
    } else {
        std::for_each(pixel_array_.rbegin(), pixel_array_.rend(), load_row);
    }

    if (stream.fail()) {
        throw LoadingFailedException();
    }
}

void TImage::Write(std::ostream& stream) const {
    const auto padding = static_cast<std::streamsize>(Width() % 4);

    bmp_header_.Write(stream);
    dib_header_.Write(stream);

    const auto write_row = [&stream, padding](const std::vector<TColor>& pixel_row) {
        for (const auto& pixel : pixel_row) {
            pixel.Write(stream);
        }
        for (std::streamsize i = 0; i < padding; ++i) {
            stream.put(0);
        }
    };

    if (dib_header_.Height() < 0) {
        std::for_each(pixel_array_.begin(), pixel_array_.end(), write_row);
    } else {
        std::for_each(pixel_array_.rbegin(), pixel_array_.rend(), write_row);
    }
}

void TImage::ChangeHeight(size_t new_height) {
    pixel_array_.resize(new_height, std::vector<TColor>(Width(), TColor()));
    dib_header_.Height() = static_cast<int32_t>(new_height) * ((dib_header_.Height() < 0) ? -1 : 1);
}

void TImage::ChangeWidth(size_t new_width) {
    std::for_each(pixel_array_.begin(), pixel_array_.end(),
                  [new_width](auto& row) { row.resize(new_width, TColor()); });
    dib_header_.Width() = static_cast<uint32_t>(new_width);
}

size_t TImage::Height() const {
    return pixel_array_.size();
}

size_t TImage::Width() const {
    return pixel_array_.empty() ? 0 : pixel_array_[0].size();
}

std::vector<TColor> TImage::CopyRow(size_t x) const {
    return pixel_array_[x];
}

std::vector<TColor> TImage::CopyColumn(size_t x) const {
    std::vector<TColor> res;
    res.reserve(Height());
    for (size_t i = 0; i < Height(); ++i) {
        res.push_back(pixel_array_[i][x]);
    }
    return res;
}
