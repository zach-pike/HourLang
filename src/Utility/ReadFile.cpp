#include "ReadFile.hpp"


std::string ReadFile(std::filesystem::path path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}