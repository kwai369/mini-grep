#include "matcher.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>

std::vector<Match> find_matches(const std::filesystem::path& filepath, const std::string& pattern) {
    std::ifstream inputfile(filepath);
    if (!inputfile.is_open()) {
        std::cerr << "Error: Failed to open file " << filepath.string() << "\n";
        return {};
    }

    std::vector<Match> matches;
    std::string line;
    int linenumber = 1;
    
    while (std::getline(inputfile, line)) {
        std::string original_line = line;
        to_lowercase(line);
        if (line.find(pattern) != std::string::npos) {
            matches.push_back({linenumber, original_line});
        }
        linenumber++;
    }

    return matches;
}