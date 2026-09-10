#include "core.hpp"
#include "traversal.hpp"
#include <utility>

namespace fs = std::filesystem;

std::vector<FileResult> process_path(const fs::path& target_path, const std::string& pattern, bool recursive) {
    std::vector<FileResult> result;

    for (const auto& file : collect_files(target_path, recursive)) {
        std::vector<Match> matches = find_matches(file, pattern);
        if (!matches.empty()) {
            result.push_back({file.string(), std::move(matches)});
        }
    }
    return result;
}

