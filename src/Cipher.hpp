#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

namespace Ciphers {
    class Cipher {
        public:
            // Cipher destruct
            virtual ~Cipher(void) = default;

            // Initializer
            virtual void Init(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) = 0; 

            // Cipher update
            virtual void Update(const uint8_t* in, size_t len, std::vector<uint8_t>& out) = 0;

            // Finalize cipher steps
            virtual void Final(std::vector<uint8_t>& out) = 0;
    }; // Cipher class
} // Ciphers