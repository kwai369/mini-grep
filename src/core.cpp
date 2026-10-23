#include "core.hpp"
#include "traversal.hpp"
#include <fstream>
#include <iostream>
#include <utility>

namespace fs = std::filesystem;

SearchResult process_path(const fs::path& target_path, const std::string& pattern, bool recursive) {
    SearchResult result;

    FileList list = collect_files(target_path, recursive);
    result.had_error = list.had_error;
    
    for (const auto& file : list.files) {
        std::ifstream inputfile(file);
        if (!inputfile.is_open()) {
            std::cerr << "my_clt: " << file.string() << ": cannot open file\n";
            result.had_error = true; 
            continue;
        }
        std::vector<Match> matches = find_matches(inputfile, pattern);
        if (!matches.empty()) {
            result.files.push_back({file.string(), std::move(matches)});
        }
    }
    
    return result;
}