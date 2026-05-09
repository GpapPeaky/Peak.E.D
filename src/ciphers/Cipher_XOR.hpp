#pragma once

#include "../Cipher.hpp"

namespace Ciphers {
    class XOR : public Cipher {
        private:
            std::vector<UINT32> key; // Cipher key

        public:
            // Construct
            XOR(void);
        
            // Initializer
            void Init(const std::vector<UINT32>& key, const std::vector<UINT32>& iv) override ;
    
            // Cipher update
            void Update(const UINT32* in, size_t len, std::vector<UINT32>& out) override ;
    
            // Finalize cipher steps
            void Final(std::vector<UINT32>& out) override ;
    }; // XOR Cipher
} // Ciphers