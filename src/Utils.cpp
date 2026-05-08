#include "Utils.hpp"

namespace Utils {
    bool exists(const std::string& fname) {
        namespace fs = std::filesystem;
           
        return fs::exists(fname);
    }
} // Utils