#pragma once

#include "interfaces/ILoadable.h"
#include "interfaces/IWritable.h"

#include <cstdint>

class TColor : public ILoadable, public IWritable {
public:
    using ValueType = double;

    static const ValueType COLOR_MAX_VALUE;

    TColor();
    explicit TColor(ValueType r, ValueType g, ValueType b);
    explicit TColor(uint8_t r, uint8_t g, uint8_t b);

    void Load(std::istream& stream) override;
    void Write(std::ostream& stream) const override;

    TColor operator+(const TColor& rhs) const;
    TColor operator-(const TColor& rhs) const;
    TColor operator*(ValueType x) const;

    TColor& operator+=(const TColor& rhs);
    TColor& operator-=(const TColor& rhs);
    TColor& operator*=(ValueType x);

    void AddPixelMultipliedBy(const TColor& other, ValueType k);

    virtual ~TColor() = default;

    ValueType R;
    ValueType G;
    ValueType B;

private:
    static ValueType ToValueType(uint8_t x);
    static uint8_t ToInteger(ValueType x);
};
