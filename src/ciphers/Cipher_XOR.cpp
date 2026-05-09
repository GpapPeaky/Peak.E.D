#include "Cipher_XOR.hpp"

namespace Ciphers {
    XOR::XOR(void) {}
    
    void XOR::Init(const std::vector<UINT32>& key, const std::vector<UINT32>& iv) {
        this->key = key;
    }
    
    void XOR::Update(const UINT32* in, size_t len, std::vector<UINT32>& out) {
        out.resize(len);
        
        for (size_t i = 0 ; i < len ; i++) {
            out[i] = in[i] ^ key[0]; // Takes only the first part 
        }    
    }
    
    void XOR::Final(std::vector<UINT32>& out) {
        // NOOP    
    }
} // Ciphers