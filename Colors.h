#pragma once

#include "TColor.h"

namespace color {
const TColor WHITE = TColor(static_cast<uint8_t>(255), 255, 255);
const TColor BLACK = TColor();
const TColor RED = TColor(static_cast<uint8_t>(255), 0, 0);
const TColor GREEN = TColor(static_cast<uint8_t>(0), 255, 0);
const TColor BLUE = TColor(static_cast<uint8_t>(0), 0, 255);
}  // namespace color
