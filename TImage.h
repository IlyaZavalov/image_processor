#pragma once

#include "TColor.h"
#include "headers/TBMPHeader.h"
#include "headers/TDIBHeader.h"
#include "interfaces/ILoadable.h"
#include "interfaces/IWritable.h"

#include <vector>

class BadHeaderException : public std::invalid_argument {
public:
    BadHeaderException() : std::invalid_argument("only BITMAPINFOHEADER DIB header is supported") {
    }
};

class TImage : public ILoadable, public IWritable {
public:
    using PixelArray = std::vector<std::vector<TColor>>;

    TImage() = default;
    TImage(const TImage& other);
    TImage(TImage&& other);

    explicit TImage(TBMPHeader bmp_header, TDIBHeader dib_header, const PixelArray& pixel_array);
    explicit TImage(TBMPHeader bmp_header, TDIBHeader dib_header, PixelArray&& pixel_array);

    TImage& operator=(const TImage& rhs);
    TImage& operator=(TImage&& rhs);

    std::vector<TColor>& operator[](size_t index);
    const std::vector<TColor>& operator[](size_t index) const;

    void Load(std::istream& stream) override;
    void Write(std::ostream& stream) const override;

    void ChangeHeight(size_t new_height);
    void ChangeWidth(size_t new_width);

    size_t Height() const;
    size_t Width() const;

    std::vector<TColor> CopyRow(size_t x) const;
    std::vector<TColor> CopyColumn(size_t x) const;

private:
    TBMPHeader bmp_header_;
    TDIBHeader dib_header_;
    PixelArray pixel_array_;
};
