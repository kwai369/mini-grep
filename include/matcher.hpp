#pragma once
#include <string>
#include <vector>
#include <array>
#include <cstddef>
#include <iosfwd> // std::istream 

struct Match {
    int linenumber;
    std::string linecontent;
};

// Boyer-Moore-Horspool substring search, with the shift table 
// precomputed once from the pattern and reused across many searches.
class PatternSearcher {
    public:
        explicit PatternSearcher(const std::string& pattern);

        // True if the pattern occurs anywhere in text.
        bool contains(const std::string& text) const;

    private:
        std::string pattern_;
        std::array<std::size_t, 256> shift_;
}; 

// Search any input stream for the pattern, returning all matching lines.
std::vector<Match> find_matches(std::istream& input, const std::string& pattern);