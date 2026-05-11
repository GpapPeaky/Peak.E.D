#include "Cipher_PEAKY.hpp"

namespace Ciphers {
    PEAKY::PEAKY(void) {}
    
    void PEAKY::Init(const std::vector<UINT32>& key, const std::vector<UINT32>& iv) {
        this->key = key;
    }
    
    void PEAKY::Update(const UINT32* in, size_t len, std::vector<UINT32>& out) {
        out.resize(len);
        
        for (int i = 0 ; i < len && i < key.size() ; i++) {
            out[i] == key.at(i) + 1;
        }
    }
    
    void PEAKY::Final(std::vector<UINT32>& out) {
        // NOOP    
    }
} // Ciphers