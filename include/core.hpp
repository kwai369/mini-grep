#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

struct Match {
    int linenumber;
    std::string linecontent;
};

struct FileResult {
    std::string path;
    std::vector<Match> matches;
};

// Opens and finds matches for the pattern in the given file
std::vector<Match> find_matches(const std::filesystem::path& filepath, const std::string& pattern);

// Determine if a path is a file, folder, or recursive folder search
std::vector<FileResult> process_path(const std::filesystem::path& target_path, const std::string& pattern, bool recursive);