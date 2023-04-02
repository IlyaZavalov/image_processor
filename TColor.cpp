#include "TColor.h"

const TColor::ValueType TColor::COLOR_MAX_VALUE = 255.;

TColor::TColor() : R(0), G(0), B(0) {
}

TColor::TColor(ValueType r, ValueType g, ValueType b) : R(r), G(g), B(b) {
}

TColor::TColor(uint8_t r, uint8_t g, uint8_t b) {
    R = ToValueType(r);
    G = ToValueType(g);
    B = ToValueType(b);
}

void TColor::Load(std::istream& stream) {
    B = ToValueType(stream.get());
    G = ToValueType(stream.get());
    R = ToValueType(stream.get());
    if (stream.fail()) {
        throw LoadingFailedException();
    }
}

void TColor::Write(std::ostream& stream) const {
    stream.put(static_cast<char>(ToInteger(B)));
    stream.put(static_cast<char>(ToInteger(G)));
    stream.put(static_cast<char>(ToInteger(R)));
}

TColor TColor::operator+(const TColor& rhs) const {
    TColor res = *this;
    res += rhs;
    return res;
}

TColor TColor::operator-(const TColor& rhs) const {
    TColor res = *this;
    res -= rhs;
    return res;
}

TColor TColor::operator*(ValueType x) const {
    TColor res = *this;
    res *= x;
    return res;
}

TColor& TColor::operator+=(const TColor& rhs) {
    R += rhs.R;
    G += rhs.G;
    B += rhs.B;
    return *this;
}

TColor& TColor::operator-=(const TColor& rhs) {
    R -= rhs.R;
    G -= rhs.G;
    B -= rhs.B;
    return *this;
}

TColor& TColor::operator*=(ValueType x) {
    R *= x;
    G *= x;
    B *= x;
    return *this;
}

TColor::ValueType TColor::ToValueType(uint8_t x) {
    return static_cast<ValueType>(x) / COLOR_MAX_VALUE;
}

uint8_t TColor::ToInteger(ValueType x) {
    return static_cast<uint8_t>(x * COLOR_MAX_VALUE);
}

void TColor::AddPixelMultipliedBy(const TColor& other, TColor::ValueType k) {
    R += other.R * k;
    G += other.G * k;
    B += other.B * k;
}
