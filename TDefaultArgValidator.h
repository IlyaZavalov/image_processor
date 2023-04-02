#pragma once

#include "aliases.h"

#include <sstream>

struct TDefaultArgValidator {
    template <typename T>
    static bool Validate(TArgType s) {
        if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view>) {
            return true;
        }

        if constexpr (std::is_integral_v<T>) {
            auto begin = s.begin();
            if constexpr (std::is_signed_v<T>) {
                if (!s.empty() && s[0] == '-') {
                    ++begin;
                }
            }
            return begin != s.end() && std::all_of(begin, s.end(), isdigit);
        }

        if constexpr (std::is_floating_point_v<T>) {
            std::stringstream ss;
            float float_value = 0;
            ss << s;
            ss >> float_value;
            return ss.eof() && !ss.fail();
        }

        throw std::invalid_argument("TDefaultArgValidator::Validate : unsupported type");
    }
};
