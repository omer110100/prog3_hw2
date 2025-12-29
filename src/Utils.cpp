#include "Utils.h"
#include <cctype>
#include <sstream>

namespace utils {

std::string toLower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

std::vector<std::string> splitWS(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> out;
    std::string token;
    while (iss >> token) out.push_back(token);
    return out;
}

}
