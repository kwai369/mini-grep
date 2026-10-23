#include "cli.hpp"
#include "core.hpp"
#include "matcher.hpp"
#include "output.hpp"
#include <iostream>
#include <stdexcept>

namespace exit_code {
    constexpr int match = 0;
    constexpr int no_match = 1;
    constexpr int error = 2; 
}

int main(int argc, char* argv[]) {
    try {
        // Parse Inputs (Input Module)
        Config config = parse_arguments(argc, argv);

        bool any_match = false;
        bool any_error = false;

        // Execution Logic (Core Module)
        if (config.target_paths.empty()) {
            // No files given read from standard input.
            std::vector<Match> matches = find_matches(std::cin, config.pattern);
            if (!matches.empty()) {
                any_match = true;
                std::vector<FileResult> results;
                results.push_back({"(standard input)", std::move(matches)});
                output_formatter(results);
            }
        } else{
            // If target path is given iterate through the paths.
            for (const auto& path : config.target_paths) {
                SearchResult results = process_path(path, config.pattern, config.recursive);
                if(results.had_error) any_error = true;
                if(!results.files.empty()) any_match = true;
                output_formatter(results.files); 
            }
        }

        if (any_error) return exit_code::error;
        return any_match ? exit_code::match : exit_code::no_match;

    } catch (const std::exception& e) {
        // Centralized Error Handling
        std::cerr << e.what() << "\n";
        return exit_code::error;
    }
}