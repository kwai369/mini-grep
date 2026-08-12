#include "cli.hpp"
#include "utils.hpp"
#include <stdexcept>

Config parse_arguments(int argc, char* argv[]) {
    Config config;

    if (argc < 4) {
        throw std::invalid_argument("Usage: grep [-r] <pattern> <file1> [file2 ...]");
    }

    if (std::string_view(argv[1]) != "grep") {
        throw std::invalid_argument("Error: Invalid command passed");
    }

    int pattern_index = 2;
    if (std::string_view(argv[2]) == "-r") {
        config.recursive = true;
        pattern_index = 3;

        if (argc < 5) {
            throw std::invalid_argument("Usage: grep [-r] <pattern> <file1> [file2 ...]");
        }
    }

    config.pattern = argv[pattern_index];
    if (config.pattern.empty()) {
        throw std::invalid_argument("Error: Empty patterns are not allowed");
    }
    
    to_lowercase(config.pattern); // Standardizing input via utils

    // Collect all target paths
    for (int i = pattern_index + 1; i < argc; i++) {
        std::string path_arg = argv[i];
        if (!path_arg.empty()) {
            config.target_paths.push_back(path_arg);
        }
    }

    if (config.target_paths.empty()) {
        throw std::invalid_argument("Error: No valid target paths provided");
    }

    return config;
}