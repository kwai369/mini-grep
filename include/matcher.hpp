#pragma once
#include <string>
#include <vector>
#include <array>
#include <cstddef>
#include <iosfwd> // std::istream 
#include "options.hpp"

struct Match {
    int linenumber;
    std::string linecontent;
};

// Boyer-Moore-Horspool substring search, with the shift table 
// precomputed once from the pattern and reused across many searches.
class PatternSearcher {
    public:
        PatternSearcher(const std::string& pattern, bool ignore_case);

        // True if the pattern occurs anywhere in text.
        bool contains(const std::string& text) const;

    private:
        unsigned char fold(char c) const {
            return fold_[static_cast<unsigned char>(c)];
        }

        std::string pattern_; // stored already folded
        std::array<std::size_t, 256> shift_; // indexed by folded byte
        std::array<unsigned char, 256> fold_; // byte -> comparison byte
}; 

// Search any input stream for the pattern, returning all matching lines.
std::vector<Match> find_matches(std::istream& input, const std::string& pattern, const SearchOptions& options);