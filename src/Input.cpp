#include "Input.hpp"

namespace Tokenization {
    std::vector<std::string> gInputFiles;
    
    void TokenizeInput(unsigned int argumentCount, char** argumentVector) {
        for (unsigned int i = 1 ; i < argumentCount ; i++) {
            std::string argumentStr = std::string(argumentVector[i]);

            bool isFile = false;
            
            // Run through the flags vector, mark flags as active if matching
            for (unsigned char idx = 0 ; idx < Flagging::gFlags.size() ; idx++) {
                if (Flagging::gFlags[idx].ID() == argumentStr) { // Check for flags
                    Flagging::gFlags[idx].Activate(); // Activate flag
                    
                    isFile = false;
                    
                    break; // Record once, break to not intervene
                           // in file recording 
                } else if (idx == 0 && Flagging::gFlags[0].ID() == argumentStr.substr(0, 4)) {
                    // Key record
                    Functions::ReadKey(argumentStr);
                    
                    isFile = false;
                    
                    break;
                } else { // File
                    isFile = true; // Check for file names
                                        
                    continue;
                }
            } // Flagging
            
            if (isFile) {
                if (Utils::exists(argumentStr)) {
                    gInputFiles.push_back(argumentStr);
                } else {
                    std::cerr << "Please provide an existing file as input, " << argumentStr << " doesn't exist\n";
                    
                    exit(-10);
                }
            }
        } // Argument reading
    }
} // Tokenization