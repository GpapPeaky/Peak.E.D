#include "Input.hpp"

#include "Cipher.hpp"
#include "ciphers/Cipher_XOR.hpp"

int main(int argc, char** argv) {
    // Arguments and argument count include the program name as well
    if (argc == 1) {
        std::cerr << "No arguments provided, please provided a file to read and a flag\n";
        
        return -1;
    }
    
    Flagging::PopulateFlags();
    
    // Tokenize input
    Tokenization::TokenizeInput((unsigned int)argc, argv);
    
    // Cipher defaulting
    Ciphers::Cipher* activeCipher = nullptr;    
    
    if (Tokenization::gInputFiles.empty()) {
        std::cerr << "Please provide at least one input file to read\n";
        
        return -2;
    }

    // Input process pipeline, O(n) of flags, no need to do 3 * O(n)
    
    // Save, so we pass the pipeline once
    size_t lastPipelineIndex                = 0;
    size_t pipelineSize                     = Flagging::gFlags.size();
    unsigned char readFlagsPerPipelineStage = 0;
    
    // Preprocess
    for (size_t index = 1 ; ; index++) {
        if (index >= pipelineSize) break;
        // Extract flag
        Flagging::Flag flag = Flagging::gFlags.at(index);
        
        if (!flag.Active()) continue;
        if (flag.CTX() != Flagging::FlagContext::PREPROCESS_FLAG) break; // End of preprocessing
        
        flag.Pre(activeCipher); // Select a valid cipher via a preprocess flag
        
        // readFlagsPerPipelineStage++; // We check if preprocessing is correct via the activeCipher variable
        
        lastPipelineIndex = index;
    }
    
    if (activeCipher == nullptr) {
        std::cerr << "Please provide a valid cipher for encryption/decryption\n";
        return -3;
    }

    // File streams, will save the output to one tmp file for now
    // TODO
    //    We need to update the pipeline for encrypting/decrypting all inputed files, later
    std::ifstream in(Tokenization::gInputFiles.at(0));
    std::ofstream out(Tokenization::gInputFiles.at(0) + ".tmp");

    // Runtime
    for (size_t index = lastPipelineIndex + 1 ; ; index++) {
        if (index >= pipelineSize) break;
        
        // Extract flag
        Flagging::Flag flag = Flagging::gFlags.at(index);
        
        if (!flag.Active()) continue;
        if (flag.CTX() != Flagging::FlagContext::RUNTIME_FLAG) break; // End of runtime
        
        flag.Runtime(in, out, activeCipher);
        
        readFlagsPerPipelineStage++;
        
        lastPipelineIndex = index;
    }
        
    if (readFlagsPerPipelineStage == 0) {
        std::cerr << "Please provide at least one runtime flag \"-e\" for encrypting or \"-d\" for decrypting\n";
        return -4;
    }
    
    // Postprocessing is not required.
    
    // Postprocess    
    for (size_t index = lastPipelineIndex + 1; ; index++) {
        if (index >= pipelineSize) break;
        
        // Extract flag
        Flagging::Flag flag = Flagging::gFlags.at(index);
        
        if (!flag.Active()) continue;
        if (flag.CTX() != Flagging::FlagContext::POSTPROCESS_FLAG) break; // End of postprocess
    }
    
    return 0;
}