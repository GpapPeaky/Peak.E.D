#pragma once

#include <filesystem>
#include <vector>

// Unsigned 32-bit integer
typedef unsigned int UINT32;

namespace Utils {
    // Check if a file exists
    bool exists(const std::string& fname);
} // Utils