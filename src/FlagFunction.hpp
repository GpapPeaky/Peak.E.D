#pragma once

#include "Cipher.hpp"
#include "ciphers/Cipher_XOR.hpp"

#include "Utils.hpp"

#include <fstream>
#include <iostream>

namespace Functions {
    /* 
     * Dedicated flag functions
     * 
     * in:     Input to encyrption/decryption 
     * out:    Where to print the output
     * cipher: Cipher for encryption/decryption
    */
    using RuntimeFn = void(*)(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher);
    
    /* 
     * Dedicated flag functions
     * 
     * cipher: Cipher to use
    */
    using PreprocessFn = void(*)(Ciphers::Cipher*& cipher);

    /* 
     * Dedicated flag functions
     * 
     * argument: Argument to extract the key from
    */
    using KeyFn = void(*)(std::string& argument);

    // Encrypt a file
    void Encrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher);
    
    // Decrypt a file
    void Decrypt(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher);
    
    // Show toggle
    void Print(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher);

    // No operation, for runtime flags, assigning ciphers
    void Noop(std::ifstream& in, std::ofstream& out, Ciphers::Cipher*& cipher);
    void Noop(Ciphers::Cipher*& cipher);
    void Noop(std::string& argument);

    void ReadKey(std::string& argument);

    // Assign cipher
    void AssignXOR(Ciphers::Cipher*& cipher);

    // Printing lock
    extern bool gPrintLock;
    
    // Key if required, might get used by a cipher, maybe not, assigning it to simple ciphers does nothing
    extern uint8_t* gKey; 
} // Flagging