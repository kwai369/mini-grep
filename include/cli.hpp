#pragma once
#include <string>
#include <vector>
#include <string_view>

// This struct will hold all runtime arguments.
struct Config {
    bool recursive = false;
    std::string pattern;
    std::vector<std::string> target_paths;
};

// Parses argc/argv and returns a fully populated Config object
Config parse_arguments(int argc, char* argv[]);