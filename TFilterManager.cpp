#include "TFilterManager.h"

TFilterManager::TFilterManager(const TFiltersInfo& supported_filters) : supported_filters_(supported_filters) {
}

TFilterManager::TFilterManager(TFiltersInfo&& supported_filters) : supported_filters_(std::move(supported_filters)) {
}

const TFiltersInfo& TFilterManager::GetSupportedFilters() const {
    return supported_filters_;
}

void TFilterManager::AddFilter(const TParsedFilter& list) {
    const auto& [filter, args] = list;
    added_filters_.push_back(supported_filters_[filter].create(args));
}

void TFilterManager::AddFilters(const TParsedFilters& filters) {
    for (const auto& filter : filters) {
        AddFilter(filter);
    }
}

void TFilterManager::ApplyFilters(TImage& image) {
    for (const auto& filter : added_filters_) {
        filter->Apply(image);
    }
}
