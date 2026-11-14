#include "cli.hpp"
#include <stdexcept>

Config parse_arguments(int argc, char* argv[]) {
    Config config;

    if (argc < 2) {
        throw std::invalid_argument("Usage: grep [-r] [-i] [--] <pattern> <file1> [file2 ...]");
    }

    int index = 1;
    
    while (index < argc) {
        std::string_view arg = argv[index];

        if (arg == "--") {
            ++index;
            break;
        }
        if (arg.size() < 2 || arg[0] != '-') {
            break;
        }

        if (arg == "-r") {
            config.recursive = true;
        } else if (arg == "-i") {
            config.search.ignore_case = true;
        } else {
            throw std::invalid_argument("Error: Unknown flag: " + std::string(arg));
        }
        ++index;
    }

    if (index >= argc) {
        throw std::invalid_argument("Error: No pattern provided");
    }

    config.pattern = argv[index];
    if (config.pattern.empty()) {
        throw std::invalid_argument("Error: Empty patterns are not allowed");
    }
    
    index++;

    // Collect all target paths
    for (int i = index; i < argc; i++) {
        std::string path_arg = argv[i];
        if (!path_arg.empty()) {
            config.target_paths.push_back(path_arg);
        }
    }

    return config;
}