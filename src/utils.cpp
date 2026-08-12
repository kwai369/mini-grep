#include "utils.hpp"
#include <algorithm>
#include <cctype>

void to_lowercase(std::string& convert) {
    std::transform(convert.begin(), convert.end(), convert.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}