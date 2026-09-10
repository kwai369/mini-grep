#include "output.hpp"
#include <iostream>

namespace fs = std::filesystem;

void output_formatter(const std::vector<FileResult>& formatter) {
    for(const auto& file: formatter) {
        std::cout << "\n---- Matches found in: " << file.path << " ----\n"; 
            
        for (const auto& match : file.matches) {
            std::cout << "Line " << match.linenumber << ":\n" << match.linecontent << "\n";
        }
        
        std::cout << "Total Matches: " << file.matches.size() << "\n";
    }
}