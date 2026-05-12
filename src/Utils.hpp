#pragma once

#include <filesystem>
#include <vector>
#include <iostream>

// Unsigned 32-bit integer
typedef unsigned int UINT32;

// Unsigned 8-bit integer / 1-Byte
typedef unsigned char UINT8;

namespace Utils {
    // Check if a file exists
    bool exists(const std::string& fname);
} // Utils