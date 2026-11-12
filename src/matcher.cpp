#include "matcher.hpp"
#include <cctype>
#include <istream>

PatternSearcher::PatternSearcher(const std::string& pattern, bool ignore_case) {
    // Builds the fold table
    for (std::size_t b = 0; b < fold_.size(); ++b) {
        fold_[b] = ignore_case ? static_cast<unsigned char>(std::tolower(static_cast<int>(b))) : static_cast<unsigned char>(b);
    }   

    // Store the pattern in folded form
    pattern_.reserve(pattern.size());
    for (char c : pattern) {
        pattern_.push_back(static_cast<char>(fold(c)));
    }

    // Build the shift table over the folded pattern
    const std::size_t m = pattern_.size();
    shift_.fill(m);
    for (std::size_t i = 0; i + 1 < m; ++i) {
        shift_[static_cast<unsigned char>(pattern_[i])] = m - 1 - i;
    }
}

bool PatternSearcher::contains(const std::string& text) const {
    const std::size_t m = pattern_.size();
    const std::size_t n = text.size();
    if (m == 0) return true;
    if (n < m) return false;

    std::size_t s = 0; // Current alginment of pattern against text
    while (s <= n - m) {
        std::size_t j = m - 1;
        // Compare folded text against the already-folded pattern
        // The cast matters, plain text may be signed, fold() returns unsigned.
        while (fold(text[s + j]) == static_cast<unsigned char>(pattern_[j])) {
            if (j == 0) return true;
            --j;
        }
        // Shift base on the text character aligned with the END of the window - not the mismatch point.
        s += shift_[fold(text[s + m - 1])];
    }
    
    return false;
}

std::vector<Match> find_matches(std::istream& input, const std::string& pattern, const SearchOptions& options) {
    PatternSearcher searcher(pattern, options.ignore_case); 
    
    std::vector<Match> matches;
    std::string line;
    int linenumber = 1;
    
    while (std::getline(input, line)) {
        if (searcher.contains(line)) {
            matches.push_back({linenumber, line});
        }
        linenumber++;
    }

    return matches;
}