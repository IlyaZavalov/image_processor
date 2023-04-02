#pragma once

#include "aliases.h"

#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <sstream>

template <typename... Args>
struct TArgsValidator;

template <typename ArgValidator>
struct TArgsValidator<ArgValidator> {
    static bool Validate(const TArgList& args) {
        return size(args) == 0;
    }

    static bool ValidateByIterator(TArgList::const_iterator) {
        return true;
    }

    static size_t ArgumentsCount() {
        return 0;
    }
};

template <typename ArgValidator, typename First, typename... Rest>
struct TArgsValidator<ArgValidator, First, Rest...> {
    static bool Validate(const TArgList& args) {
        if (size(args) != 1 + sizeof...(Rest)) {
            return false;
        }
        return ValidateByIterator(cbegin(args));
    }

    static bool ValidateByIterator(TArgList::const_iterator it) {
        return ArgValidator::template Validate<First>(*it) &&
               TArgsValidator<ArgValidator, Rest...>::ValidateByIterator(std::next(it));
    }

    static size_t ArgumentsCount() {
        return 1 + sizeof...(Rest);
    }
};
