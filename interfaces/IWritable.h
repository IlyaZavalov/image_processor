#pragma once

#include <ostream>

class IWritable {
public:
    virtual void Write(std::ostream& stream) const = 0;
};