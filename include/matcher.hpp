#pragma once
#include <string>
#include <vector>
#include <filesystem>

struct Match {
    int linenumber;
    std::string linecontent;
};

// Search a single file for the pattern, returning all matching lines.
std::vector<Match> find_matches(const std::filesystem::path& filepath, const std::string& pattern);