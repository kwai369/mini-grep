#include "traversal.hpp"
#include <iostream>

namespace fs = std::filesystem;

std::vector<fs::path> collect_files(const fs::path& target_path, bool recursive) {
    std::vector<fs::path> files;

    if (!fs::exists(target_path)) {
        std::cerr << "Error: Path does not exist: " << target_path.string() << "\n";
        return files;
    }

    if (fs::is_regular_file(target_path)) {
        files.push_back(target_path);
    } else if (fs::is_directory(target_path)) {
        if (recursive) {
            for (const auto& entry : fs::recursive_directory_iterator(target_path)) 
                if (fs::is_regular_file(entry.path()))
                    files.push_back(entry.path()); 
        } else {
            for (const auto& entry : fs::directory_iterator(target_path))
                if(fs::is_regular_file(entry.path()))
                    files.push_back(entry.path());
        }
    }
    return files;
}