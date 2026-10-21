#pragma once
#include <vector>
#include <filesystem>

struct FileList {
    std::vector<std::filesystem::path> files;
    bool had_error = false; // true if anything couldn't be read
};

// Expand a target path into the list of regular files to search.
// Never throws for filesystem errors; reports them to stderr and sets had_error.
FileList collect_files(const std::filesystem::path& target_path, bool recursive);