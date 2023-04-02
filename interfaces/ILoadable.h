#pragma once

#include <istream>
#include <stdexcept>

class LoadingFailedException : public std::runtime_error {
public:
    LoadingFailedException() : std::runtime_error("loading failed") {
    }
};

class ILoadable {
public:
    virtual void Load(std::istream& stream) = 0;
};
