#include "cli.hpp"
#include "core.hpp"
#include "matcher.hpp"
#include "output.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        // Parse Inputs (Input Module)
        Config config = parse_arguments(argc, argv);

        // Execution Logic (Core Module)
        if (config.target_paths.empty()) {
            // No files given read from standard input.
            std::vector<Match> matches = find_matches(std::cin, config.pattern);
            if (!matches.empty()) {
                std::vector<FileResult> results;
                results.push_back({"(standard input)", std::move(matches)});
                output_formatter(results);
            }
        } else{
                // If target path is given iterate through the paths.
                for (const auto& path : config.target_paths) {
                std::vector<FileResult> results = process_path(path, config.pattern, config.recursive);
                output_formatter(results); 
            }
        }
    } catch (const std::exception& e) {
        // Centralized Error Handling
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}