#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdio>

// Flag functions functions

// Encrypt a file
void encrypt(std::ifstream& in, std::ofstream& out);

// Decrypt a file
void decrypt(std::ifstream& in, std::ofstream& out);

// Printing lock
bool showLock = false; 

// Show toggle
void show(std::ifstream& in, std::ofstream& out);

// Check if a file exists
bool exists(const std::string& fname);

// Flag total
#define FLAG_COUNT 3

// Input flags
std::string flags[] = {
    "-s",   // Show output in console
    "-e",   // Encrypt file
    "-d",   // Decrypt file
};

/// Dedicated flag functions, in
/// 
/// in:  Input to encyrpt/decrypt 
/// out: Where to print the output
typedef void (*flagFunction)(std::ifstream& in, std::ofstream& out);

// Check what is active
std::pair<bool, flagFunction> activeFlags[] = {
    {false, show},
    {false, encrypt},
    {false, decrypt},
};
    
int main(int argc, char** argv) {
    // Arguments and argument count include the program name as well
    if (argc == 1) {
        std::cerr << "No arguments provided, please provided a file to read and a flag\n";
        
        return -1;
    }

    unsigned char active = 0; 
    std::vector<std::string> inputFileNames; // Files to decrypt/encrypt

    for (unsigned int i = 1 ; i < (unsigned int)argc ; i++) {
        std::string argumentStr = std::string(argv[i]);
        
        bool isFile = false;
        
        for (unsigned char idx = 0 ; idx < FLAG_COUNT ; idx++) {
            if (flags[idx] == argumentStr) { // Check for flags
                activeFlags[idx].first = true;
                active++;
                isFile = false;
                
                break; // Record once, break to not intervene
                // in file recording 
            } else {
                isFile = true; // Check for file names
            }
        } // Flagging
        
        if (isFile) {
            if (exists(argumentStr)) {
                inputFileNames.push_back(argumentStr);
            } else {
                std::cerr << "Please provide an existing file as input, " << argumentStr << " doesn't exist\n";
                
                return -4;
            }
        }
    } // Argument reading

    if (active == 0) {
        std::cerr << "Please provide either flags, \"-e\" to encrypt or \"-d\" to decrypt\n";
        
        return -5;
    }
        
    if (inputFileNames.empty()) {
        std::cerr << "Please provide at least one input file to read\n";
        
        return -6;
    }

    // Process input
    
    // Pre-activate printing
    if (activeFlags[0].first) {
        std::ifstream in;
        std::ofstream out;
        
        in.open("FLAGACTIVATIONFILE.file");
        out.open("FLAGACTIVATIONFILE.file");
        
        // Temps, not usable
        show(in, out);
        
        in.close();
        out.close();
    }
    
    // Flags
    for (unsigned char i = 1 ; i < FLAG_COUNT ; i++) {
        if (activeFlags[i].first) {                 // since -s is first, it has priority over all flags
                                                    // , no matter where it is placed, it shadows -e and -d 
            for (auto fname : inputFileNames) {
                std::ifstream in(fname);
                std::ofstream out(fname + ".tmp");
            
                activeFlags[i].second(in, out);
            
                in.close();
                out.close();
            
                std::filesystem::rename(fname + ".tmp", fname);
            }
        }
    }
 
    return 0;
}
    
bool exists(const std::string& fname) {
    namespace fs = std::filesystem;
        
    return fs::exists(fname);
}

void show(std::ifstream& in, std::ofstream& out) {
    showLock = true;
}

void encrypt(std::ifstream& in, std::ofstream& out) {
    std::string line;

    while(getline(in, line)) {
        // Encrypt
        for (char& c : line) {
            c += 1;                
        }

        out << line << "\n";
        if (showLock) std::cout << line << "\n";
    }
}

void decrypt(std::ifstream& in, std::ofstream& out) {
    std::string line;

    while(getline(in, line)) {
        // Decrypt
        for (char& c : line) {
            c -= 1;
        }

        out << line << "\n";
        if (showLock) std::cout << line << "\n";
    }
}    