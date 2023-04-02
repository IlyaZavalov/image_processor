#pragma once

#include "TColor.h"

#include <array>
#include <string_view>
#include <vector>

using TArgType = std::string_view;
using TArgList = std::vector<TArgType>;
using TParsedFilter = std::pair<std::string_view, TArgList>;
using TParsedFilters = std::vector<TParsedFilter>;
using TMatrix = std::array<std::array<TColor::ValueType, 3>, 3>;
