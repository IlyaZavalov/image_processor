#pragma once

#include "../interfaces/ILoadable.h"
#include "../interfaces/IWritable.h"

#include <tuple>

template <typename... Args>
class THeader : public ILoadable, public IWritable {
public:
    THeader() = default;

    template <size_t Index>
    auto& Get() {
        return std::get<Index>(data_);
    }

    template <size_t Index>
    const auto& Get() const {
        return std::get<Index>(data_);
    }

    void Load(std::istream& stream) override {
        std::apply([&stream](auto&&... args) { (stream.read(reinterpret_cast<char*>(&args), sizeof(args)), ...); },
                   data_);
        if (stream.fail()) {
            throw LoadingFailedException();
        }
    }

    void Write(std::ostream& stream) const override {
        std::apply(
            [&stream](auto&&... args) { (stream.write(reinterpret_cast<const char*>(&args), sizeof(args)), ...); },
            data_);
    }

protected:
    std::tuple<Args...> data_;
};
