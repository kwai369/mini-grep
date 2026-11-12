#pragma once
#include <string>
#include <vector>
#include <string_view>
#include "options.hpp"

// This struct will hold all runtime arguments.
struct Config {
    bool recursive = false;
    SearchOptions search;
    std::string pattern;
    std::vector<std::string> target_paths;
};

// Parses argc/argv and returns a fully populated Config object
Config parse_arguments(int argc, char* argv[]);