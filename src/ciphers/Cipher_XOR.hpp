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
    
            // Cipher update encryption
            void UpdateE(const UINT8* in, size_t len, std::vector<UINT8>& out) override ;
            
            // Cipher update decryption
            void UpdateD(const UINT8* in, size_t len, std::vector<UINT8>& out) override ;
    
            // Finalize cipher steps
            void Final(std::vector<UINT8>& out) override ;
    }; // XOR Cipher
} // Ciphers