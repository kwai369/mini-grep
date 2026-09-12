#include "core.hpp"
#include "traversal.hpp"
#include <fstream>
#include <iostream>
#include <utility>

namespace fs = std::filesystem;

std::vector<FileResult> process_path(const fs::path& target_path, const std::string& pattern, bool recursive) {
    std::vector<FileResult> result;

    for (const auto& file : collect_files(target_path, recursive)) {
        std::ifstream inputfile(file);
        if (!inputfile.is_open()) {
            std::cerr << "Error: Failed to open file " << file.string() << "\n";
            continue;
        }
        std::vector<Match> matches = find_matches(inputfile, pattern);
        if (!matches.empty()) {
            result.push_back({file.string(), std::move(matches)});
        }
    }
    
    return result;
}