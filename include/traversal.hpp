#pragma once
#include <vector>
#include <filesystem>

// Expand a target path into the list of regular files to search.
std::vector<std::filesystem::path> collect_files(const std::filesystem::path& target_path, bool recursive);