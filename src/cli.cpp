#include "cli.hpp"
#include "utils.hpp"
#include <stdexcept>

Config parse_arguments(int argc, char* argv[]) {
    Config config;

    if (argc < 3) {
        throw std::invalid_argument("Usage: grep [-r] <pattern> <file1> [file2 ...]");
    }

    int index = 1;
    
    while (index < argc && argv[index][0] == '-') {
        std::string_view flag = argv[index];
        if (flag == "-r"){
            config.recursive = true;
        }
        else {
            throw std::invalid_argument("Error: Unknown flag: " + std::string(flag));
        }
        index++;
    }

    if (index >= argc) {
        throw std::invalid_argument("Error: No pattern provided");
    }


    config.pattern = argv[index];
    if (config.pattern.empty()) {
        throw std::invalid_argument("Error: Empty patterns are not allowed");
    }
    
    to_lowercase(config.pattern); // Standardizing input via utils
    index++;

    // Collect all target paths
    for (int i = index; i < argc; i++) {
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