#include "FlagFunction.hpp"

namespace Functions {
    bool gPrintLock = false;

    std::vector<UINT32> gKey;
    
    // Runtimes
        
    void Print(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        gPrintLock = true;
    }
    
    void Encrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        std::vector<UINT32> buffer(4096);
        
        while(in) {
            in.read(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(UINT32));
            
            std::streamsize bytesRead = in.gcount();
            
            if (bytesRead <= 0) break; // Exit
            
            std::vector<UINT32> outbuf;
            
            size_t u32Count = static_cast<size_t>(bytesRead) / sizeof(UINT32);

            cipher->Update(buffer.data(), u32Count, outbuf);

            char* outBufferDataCharPointer = reinterpret_cast<char*>(outbuf.data());
                    
            out.write(outBufferDataCharPointer, outbuf.size() * sizeof(UINT32));
    
            if (gPrintLock) {
                std::cout.write(outBufferDataCharPointer, outbuf.size());
            }
        }
    }
    
    void Decrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        std::vector<UINT32> buffer(4096);
        
        while(in) {
            in.read(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(UINT32));
            
            std::streamsize bytesRead = in.gcount();
            
            if (bytesRead <= 0) break; // Exit
            
            std::vector<UINT32> outbuf;
            
            size_t u32Count = static_cast<size_t>(bytesRead) / sizeof(UINT32);

            cipher->Update(buffer.data(), u32Count, outbuf);
    
            char* outBufferDataCharPointer = reinterpret_cast<char*>(outbuf.data());
                    
            out.write(outBufferDataCharPointer, outbuf.size() * sizeof(UINT32));
    
            if (gPrintLock) {
                std::cout.write(outBufferDataCharPointer, outbuf.size() * sizeof(UINT32));
            }
        }
    }
        
    void Noop(std::ifstream& in, std::ofstream& out, Ciphers::Cipher& cipher) {
        // NOOP
    }
            
    // Key reading
        
    void ReadKey(std::string& argument) {
        gKey.clear();
    
        size_t firstColon = argument.find(':');
    
        if (firstColon == std::string::npos) {
            std::cerr
                << "Separator ':' not found, use format: -key:value1:value2:...\n";
    
            exit(-20);
        }
    
        std::string remaining = argument.substr(firstColon + 1);
    
        if (remaining.empty()) {
            std::cerr << "Key cannot be empty\n";
    
            exit(-21);
        }
    
        std::stringstream ss(remaining);
    
        std::string token;
    
        while (std::getline(ss, token, ':')) {
    
            if (token.empty())
                continue;
    
            bool isNumber = true;
    
            for (unsigned char c : token) {
    
                if (!std::isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
    
            // Pure numeric token
            if (isNumber) {
    
                UINT32 value = 0;
    
                for (char c : token) {
    
                    value *= 10;
    
                    value += static_cast<UINT32>(c - '0');
    
                    // UINT32 overflow wraps automatically
                }
    
                gKey.push_back(value);
    
            } else {
    
                // ASCII concatenation with natural UINT32 wraparound
                UINT32 value = 0;
    
                for (unsigned char c : token) {
    
                    std::string ascii = std::to_string(c);
    
                    for (char digit : ascii) {
    
                        value *= 10;
    
                        value += static_cast<UINT32>(digit - '0');
    
                        // UINT32 overflow wraps automatically
                    }
                }
    
                gKey.push_back(value);
            }
        }
    
        if (gKey.empty()) {
            std::cerr << "No valid keys provided\n";
    
            exit(-22);
        }
    }
    
    // Preprocessing, assigning ciphers
    
    void Noop(Ciphers::Cipher*& cipher) {
        // NOOP
    }
    
    void AssignXOR(Ciphers::Cipher*& cipher) {
        static Ciphers::XOR cipherXOR; // Persists, created once
    
        std::vector<UINT32> iv;
        
        cipherXOR.Init(Functions::gKey, iv);
            
        cipher = &cipherXOR;
    }
} // Functions