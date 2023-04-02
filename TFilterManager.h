#pragma once

#include "aliases.h"
#include "TFilterInfo.h"
#include "TImage.h"

#include <memory>

class TFilterManager {
public:
    explicit TFilterManager(const TFiltersInfo& supported_filters);
    explicit TFilterManager(TFiltersInfo&& supported_filters);
    const TFiltersInfo& GetSupportedFilters() const;
    void AddFilter(const TParsedFilter& list);
    void AddFilters(const TParsedFilters& filters);
    void ApplyFilters(TImage& image);

private:
    TFiltersInfo supported_filters_;
    std::vector<std::unique_ptr<TFilter>> added_filters_;
};
