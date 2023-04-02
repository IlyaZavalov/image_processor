#include "TArgParser.h"
#include <iostream>
#include <stdexcept>

TArgParser::TArgParser(const TFilterManager& manager) : manager_(manager) {
}

TArgParser::TParsed TArgParser::Parse(int argc, char** argv) const {
    TParsed parsed;

    if (argc == 1) {
        parsed.need_help = true;
        return parsed;
    }

    parsed.need_help = false;

    try {
        if (argc < 3) {
            throw std::invalid_argument("there must be at least two arguments (input and output file paths)");
        }
        parsed.input_file_path = std::string_view(argv[1]);
        parsed.output_file_path = std::string_view(argv[2]);

        const TFiltersInfo& supported_filters = manager_.GetSupportedFilters();
        char** end = argv + argc;

        for (char** ptr = argv + 3; ptr != end;) {
            std::string_view filter_name = *ptr;
            if (!filter_name.starts_with('-')) {
                throw std::invalid_argument("-{filter name} or --{filter name} are expected, got " +
                                            std::string(filter_name));
            }

            if (filter_name.starts_with("--")) {
                filter_name.remove_prefix(2);
            } else {
                filter_name.remove_prefix(1);
            }

            if (!supported_filters.contains(filter_name)) {
                throw std::invalid_argument("«" + std::string(filter_name) + "» is not a valid filter name");
            }

            const TFilterInfo& filter_info = supported_filters.at(filter_name);
            const size_t need_arguments = filter_info.arguments_count();

            ++ptr;
            if (static_cast<size_t>(end - ptr) < need_arguments) {
                throw std::invalid_argument("not enough arguments for " + std::string(filter_name));
            }

            TArgList arguments = {ptr, ptr + need_arguments};
            if (!filter_info.validate(arguments)) {
                throw std::invalid_argument("bad arguments for " + std::string(filter_name));
            }

            parsed.filters.emplace_back(filter_name, std::move(arguments));
            ptr += need_arguments;
        }

        return parsed;
    } catch (std::exception& e) {
        std::cout << "error: " << e.what() << "\n";
        parsed.input_file_path = "";
        parsed.output_file_path = "";
        parsed.filters.clear();
        parsed.need_help = true;
        return parsed;
    }
}
