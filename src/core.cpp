#include "core.hpp"
#include "utils.hpp"
#include <iostream>

namespace fs = std::filesystem;

std::vector<Match> find_matches(const fs::path& filepath, const std::string& pattern) {
    std::ifstream inputfile(filepath);
    if (!inputfile.is_open()) {
        std::cerr << "Error: Failed to open file " << filepath.string() << "\n";
        return {};
    }

    std::vector<Match> matches;
    std::string line;
    int linenumber = 1;
    
    while (std::getline(inputfile, line)) {
        std::string original_line = line;
        to_lowercase(line);
        if (line.find(pattern) != std::string::npos) {
            matches.push_back({linenumber, original_line});
        }
        linenumber++;
    }

    return matches;
}        

std::vector<FileResult> process_path(const fs::path& target_path, const std::string& pattern, bool recursive) {
    if (!fs::exists(target_path)) {
        std::cerr << "Error: Path does not exist: " << target_path.string() << "\n";
        return {};  
    }

    std::vector<FileResult> result;

    auto check_and_add = [&](const fs::path& path) {
        std::vector<Match> matches = find_matches(path, pattern);
        if (!matches.empty()) {
            result.push_back({path.string(), std::move(matches)});
        }
    };
    
    if (fs::is_regular_file(target_path)) {
       check_and_add(target_path);
    }
    else if (fs::is_directory(target_path)) {
        if (recursive) {
            for (const auto& entry : fs::recursive_directory_iterator(target_path)) {
                if (fs::is_regular_file(entry.path())) {
                    check_and_add(entry.path());
                }
            }
        }
        else {
            for (const auto& entry : fs::directory_iterator(target_path)) {
                if (fs::is_regular_file(entry.path())) {
                    check_and_add(entry.path());
                }
            }
        }
    }

    return result;
}