#include "matcher.hpp"
#include "utils.hpp"
#include <istream>

std::vector<Match> find_matches(std::istream& input, const std::string& pattern) {
    std::vector<Match> matches;
    std::string line;
    int linenumber = 1;
    
    while (std::getline(input, line)) {
        std::string original_line = line;
        to_lowercase(line);
        if (line.find(pattern) != std::string::npos) {
            matches.push_back({linenumber, original_line});
        }
        linenumber++;
    }

    return matches;
}