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

            // Cipher update encryption
            virtual void UpdateE(const UINT8* in, size_t len, std::vector<UINT8>& out) = 0;
            
            // Cipher update decryption
            virtual void UpdateD(const UINT8* in, size_t len, std::vector<UINT8>& out) = 0;

            // Finalize cipher steps
            virtual void Final(std::vector<UINT8>& out) = 0;
    }; // Cipher class
} // Ciphers