#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "matcher.hpp"
#include "options.hpp"

struct FileResult {
    std::string path;
    std::vector<Match> matches;
};

struct SearchResult {
    std::vector<FileResult> files;
    bool had_error = false;
};

// Orchestrates traversal + matching for a target path.
SearchResult process_path(const std::filesystem::path& target_path, const std::string& pattern, const SearchOptions& options, bool recursive);