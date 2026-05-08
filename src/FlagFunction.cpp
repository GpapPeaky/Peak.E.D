#include "FlagFunction.hpp"

namespace Functions {
    bool gPrintLock = false;

    uint8_t* gKey = nullptr;
    
    // Runtimes
        
    void Print(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        gPrintLock = true;
    }
    
    void Encrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        std::vector<uint8_t> buffer(4096);
        
        while(in) {
            in.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            
            std::streamsize bytesRead = in.gcount();
            
            if (bytesRead <= 0) break; // Exit
            
            std::vector<uint8_t> outbuf;
            
            cipher->Update(buffer.data(), static_cast<size_t>(bytesRead), outbuf);
    
            char* outBufferDataCharPointer = reinterpret_cast<char*>(outbuf.data());
                    
            out.write(outBufferDataCharPointer, outbuf.size());
    
            if (gPrintLock) {
                std::cout.write(outBufferDataCharPointer, outbuf.size());
            }
        }
    }
    
    void Decrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher) {
        std::vector<uint8_t> buffer(4096);
        
        while(in) {
            in.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            
            std::streamsize bytesRead = in.gcount();
            
            if (bytesRead <= 0) break; // Exit
            
            std::vector<uint8_t> outbuf;
            
            cipher->Update(buffer.data(), static_cast<size_t>(bytesRead), outbuf);
    
            char* outBufferDataCharPointer = reinterpret_cast<char*>(outbuf.data());
                    
            out.write(outBufferDataCharPointer, outbuf.size());
    
            if (gPrintLock) {
                std::cout.write(outBufferDataCharPointer, outbuf.size());
            }
        }
    }
        
    void Noop(std::ifstream& in, std::ofstream& out, Ciphers::Cipher& cipher) {
        // NOOP
    }
        
    // Key reading
    
    void ReadKey(std::string& argument) {
        size_t pos = argument.find(":");
    
        if (pos == std::string::npos) {
    
            std::cerr
                << "Separator ':' not found, use format: -key:value\n";
    
            exit(-20);
        }
    
        std::string keyString = argument.substr(pos + 1);
    
        if (keyString.empty()) {
    
            std::cerr << "Key cannot be empty\n";
    
            exit(-21);
        }
    
        std::string combined;
    
        for (char c : keyString) {
            combined += std::to_string(
                static_cast<int>(
                    static_cast<uint8_t>(c)
                )
            );
        }
    
        unsigned long long value =
            std::stoull(combined);
    
        static uint8_t finalKey =
            static_cast<uint8_t>(value);
    
        gKey = &finalKey;
    }
    
    // Preprocessing, assigning ciphers
    
    void Noop(Ciphers::Cipher*& cipher) {
        // NOOP
    }
    
    void AssignXOR(Ciphers::Cipher*& cipher) {
        static Ciphers::XOR cipherXOR; // Persists, created once
    
        std::vector<uint8_t> key = {0xAA}; // default key
        std::vector<uint8_t> iv;
        
        cipherXOR.Init(key, iv);
            
        cipher = &cipherXOR;
    }
} // Functions