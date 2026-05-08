#include "Cipher_XOR.hpp"

namespace Ciphers {
    XOR::XOR(void) : key(0xAA) {}
    
    void XOR::Init(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
        this->key = key[0];
    }
    
    void XOR::Update(const uint8_t* in, size_t len, std::vector<uint8_t>& out) {
        out.resize(len);
        
        for (size_t i = 0 ; i < len ; i++) {
            out[i] = in[i] ^ key; 
        }    
    }
    
    void XOR::Final(std::vector<uint8_t>& out) {
        // NOOP    
    }
} // Ciphers