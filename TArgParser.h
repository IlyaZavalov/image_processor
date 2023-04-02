#pragma once

#include "aliases.h"
#include "TFilterManager.h"

#include <string_view>
#include <vector>

class TArgParser {
public:
    struct TParsed {
        std::string_view input_file_path;
        std::string_view output_file_path;
        TParsedFilters filters;
        bool need_help;
    };

    explicit TArgParser(const TFilterManager& manager);

    TParsed Parse(int argc, char** argv) const;

private:
    const TFilterManager& manager_;
};
