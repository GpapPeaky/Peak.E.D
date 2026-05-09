#pragma once

#include "Utils.hpp"

#include <cstdint>
#include <cstddef>
#include <vector>

namespace Ciphers {
    class Cipher {
        public:
            // Cipher destruct
            virtual ~Cipher(void) = default;

            // Initializer
            virtual void Init(const std::vector<UINT32>& key, const std::vector<UINT32>& iv) = 0; 

            // Cipher update
            virtual void Update(const UINT32* in, size_t len, std::vector<UINT32>& out) = 0;

            // Finalize cipher steps
            virtual void Final(std::vector<UINT32>& out) = 0;
    }; // Cipher class
} // Ciphers