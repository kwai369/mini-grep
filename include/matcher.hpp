#pragma once
#include <string>
#include <vector>
#include <iosfwd> // std::istream - a reference param only needs the forward declaration

struct Match {
    int linenumber;
    std::string linecontent;
};

// Search any input stream for the pattern, returning all matching lines.
std::vector<Match> find_matches(std::istream& input, const std::string& pattern);