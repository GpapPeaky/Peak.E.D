#pragma once

#include "Flag.hpp"
#include "FlagContext.hpp"
#include "FlagFunction.hpp"
#include "Utils.hpp"

#include <vector>
#include <iostream>
#include <string>

namespace Tokenization {
    // Given input files
    extern std::vector<std::string> gInputFiles;

    /* Tokenizes input */
    void TokenizeInput(unsigned int argumentCount, char** argumentVector);
} // Tokenization