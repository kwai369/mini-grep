#include "matcher.hpp"
#include "utils.hpp"
#include <istream>

PatternSearcher::PatternSearcher(const std::string& pattern) : pattern_(pattern) {
    const std::size_t m = pattern_.size();
    shift_.fill(m); // default: char not in pattern -> skip the whole window

    /*For every character except the last, record its distance from the
      end of the pattern. Scanning left-to-right means a later duplicate
      overwrites an earlier one, which is what we want (rightmost wins).*/
    for (std::size_t i = 0; i+1 < m; ++i) {
        unsigned char c = static_cast<unsigned char>(pattern_[i]);
        shift_[c] = m - 1 - i;
    }   
}

bool PatternSearcher::contains(const std::string& text) const {
    const std::size_t m = pattern_.size();
    const std::size_t n = text.size();
    if (n < m) return false;

    std::size_t s = 0; // Current alginment of pattern against text
    while (s <= n - m) {
        std::size_t j = m - 1;
        while (text[s + j] == pattern_[j]) {
            if (j == 0) return true;
            --j;
        }
        // Shift base on the text character aligned with the END of the window - not the mismatch point.
        unsigned char c = static_cast<unsigned char>(text[s + m -1]);
        s += shift_[c];
    }
    
    return false;
}

std::vector<Match> find_matches(std::istream& input, const std::string& pattern) {
    PatternSearcher searcher(pattern); // preprocessed once per call, not per line
    
    std::vector<Match> matches;
    std::string line;
    int linenumber = 1;
    
    while (std::getline(input, line)) {
        std::string original_line = line;
        to_lowercase(line);
        if (searcher.contains(line)) {
            matches.push_back({linenumber, original_line});
        }
        linenumber++;
    }

    return matches;
}