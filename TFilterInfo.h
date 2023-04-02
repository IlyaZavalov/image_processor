#pragma once

#include "aliases.h"
#include "filters/TFilter.h"

#include <functional>
#include <memory>

struct TFilterInfo {
    std::function<std::unique_ptr<TFilter>(const TArgList &)> create;
    std::function<bool(const TArgList &)> validate;
    std::function<size_t()> arguments_count;
};

using TFiltersInfo = std::unordered_map<std::string_view, TFilterInfo>;

template <typename Filter>
TFilterInfo GetFilterInfo() {
    TFilterInfo result;
    result.create = Filter::Create;
    result.validate = Filter::ArgsValidator::Validate;
    result.arguments_count = Filter::ArgsValidator::ArgumentsCount;
    return result;
}
