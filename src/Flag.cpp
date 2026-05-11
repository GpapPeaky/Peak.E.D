#include "Flag.hpp"

namespace Flagging {
    std::vector<Flag> gFlags;
    
    Flag::Flag(std::string id, FlagContext fc, Functions::PreprocessFn PF) :
        fc(fc), id(id), Pre(PF) {}
    
    Flag::Flag(std::string id, FlagContext fc, Functions::RuntimeFn RF) :
        fc(fc), id(id), Runtime(RF) {}

    Flag::Flag(std::string id, FlagContext fc, Functions::KeyFn KF) :
        fc(fc), id(id), Key(KF) {}

    Flag::~Flag(void) {}

    std::string Flag::ID(void) const {
        return id;
    }

    FlagContext Flag::CTX(void) const {
        return fc;
    }
    
    void Flag::Activate(void) {
        active = true;
    }
    
    bool Flag::Active(void) const {
        return active;
    }
    
    void PopulateFlags(void) {
        // Preprocess, assign ciphers, and keys
        gFlags.emplace_back("-key",       FlagContext::KEY_FLAG,             Functions::ReadKey);
        gFlags.emplace_back("-xor",       FlagContext::PREPROCESS_FLAG,      Functions::AssignXOR);
        
        // Testing
        gFlags.emplace_back("-peak",      FlagContext::PREPROCESS_FLAG,      Functions::AssignPEAKY);
        
        // gFlags.emplace_back("-aes",       FlagContext::PREPROCESS_FLAG,      Functions::AssignAES);
        // gFlags.emplace_back("-rsa",       FlagContext::PREPROCESS_FLAG,      Functions::AssignRSA);
        // gFlags.emplace_back("-dh",        FlagContext::PREPROCESS_FLAG,      Functions::AssignDIFFIE_HOFFMAN);
        // gFlags.emplace_back("-dsa",       FlagContext::PREPROCESS_FLAG,      Functions::AssignDAS);
        // gFlags.emplace_back("-des",       FlagContext::PREPROCESS_FLAG,      Functions::AssignDES);
        // gFlags.emplace_back("-3des",      FlagContext::PREPROCESS_FLAG,      Functions::Assign3DES);
        
        // Runtime   
        gFlags.emplace_back("-e",         FlagContext::RUNTIME_FLAG,         Functions::Encrypt);
        gFlags.emplace_back("-d",         FlagContext::RUNTIME_FLAG,         Functions::Decrypt);
        gFlags.emplace_back("-p",         FlagContext::RUNTIME_FLAG,         Functions::Print);
        
        // Postprocess
        gFlags.emplace_back("-post",      FlagContext::POSTPROCESS_FLAG,     Functions::Print);
    }
} // Flagging