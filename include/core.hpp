#pragma once
#include "matcher.hpp"

struct FileResult {
    std::string path;
    std::vector<Match> matches;
};

// Orchestrates traversal + matching for a target path.
std::vector<FileResult> process_path(const std::filesystem::path& target_path, const std::string& pattern, bool recursive);