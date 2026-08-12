#include "cli.hpp"
#include "core.hpp"
#include "output.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        // Parse Inputs (Input Module)
        Config config = parse_arguments(argc, argv);
        
        // Execution Logic (Core Module)
        for (const auto& path : config.target_paths) {
            std::vector<FileResult> formatter = process_path(path, config.pattern, config.recursive);
            output_formatter(formatter); 
        }
        
    } catch (const std::exception& e) {
        // Centralized Error Handling
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}