#include "Cipher_PEAKY.hpp"

namespace Ciphers {
    PEAKY::PEAKY(void) {}
    
    void PEAKY::Init(const std::vector<UINT32>& key, const std::vector<UINT32>& iv) {
        this->key = key;
    }
    
    void PEAKY::UpdateE(const UINT8* in, size_t len, std::vector<UINT8>& out) {
        out.resize(len);
        
        for (size_t i = 0 ; i < len ; i++) {
            size_t k = i % key.size();
            
            out[i] = (in[i] ^ key[k]) +  static_cast<UINT8>(i);
        }
    }
        
    void PEAKY::UpdateD(const UINT8* in, size_t len, std::vector<UINT8>& out) {
        out.resize(len);
        
        for (size_t i = 0 ; i < len ; i++) {
            size_t k = i % key.size();
     
            out[i] = (in[i] - static_cast<UINT8>(i)) ^ key[k];
        }
    }
    
    void PEAKY::Final(std::vector<UINT8>& out) {
        // NOOP    
    }
} // Ciphers