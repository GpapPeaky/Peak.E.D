#pragma once

#include "../Cipher.hpp"

namespace Ciphers {
    class XOR : public Cipher {
        private:
            uint8_t key = 0xAA; // Cipher key    
                
        public:
            // Construct
            XOR(void);
        
            // Initializer
            void Init(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) override ;
    
            // Cipher update
            void Update(const uint8_t* in, size_t len, std::vector<uint8_t>& out) override ;
    
            // Finalize cipher steps
            void Final(std::vector<uint8_t>& out) override ;
    }; // XOR Cipher
} // Ciphers