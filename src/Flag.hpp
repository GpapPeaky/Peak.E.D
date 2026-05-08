#pragma once

#include "FlagContext.hpp"
#include "FlagFunction.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <cstdio>

namespace Flagging {
    class Flag {
        private:
            FlagContext fc;                         // Flag context
            std::string id;                         // Flag id        
            bool active;                            // If flag is active, we call its flag function
        public:
            /* Constructs */
            Flag(std::string id, FlagContext fc, Functions::PreprocessFn PF);
            Flag(std::string id, FlagContext fc, Functions::RuntimeFn RF);
            Flag(std::string id, FlagContext fc, Functions::KeyFn KF);
        
            /* Destruct */    
            ~Flag(void);
        
            /* Get flag identifier */
            std::string ID(void) const ;
            
            /* Get flag context */
            FlagContext CTX(void) const ;
    
            /* Mark flag as active */
            void Activate(void);
    
            /* Check if a flag is active */
            bool Active(void) const ;
                
            Functions::KeyFn Key = nullptr;             // Key function
        
            Functions::PreprocessFn Pre = nullptr;             // Preprocess function
    
            Functions::RuntimeFn Runtime = nullptr;            // Runtime function
    }; // Flag class
        
    // Initialize the gFlags vector, with predefined flags
    void PopulateFlags(void);
    
    // Valid and existing flags, we switch the flags active field, and call their respective FlagFunction
    // 
    // The vector's indeces can allow us to anchor flags of higher priorities first
    // 
    // The pipeline is served like this:
    // 
    // PREPROCESS -> RUNTIME -> POSTPROCESS
    // 
    // -All PREPROCESS_FLAG flags will be in the first indeces of the vector
    // -All RUNTIME_FLAG flags will be in the middle indeces of the vector
    // -All POSTPROCESS_FLAG flags will be in the final indeces of the vector
    // 
    extern std::vector<Flag> gFlags;
} // Flag