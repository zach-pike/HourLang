#include "ReadFile.hpp"


std::string ReadFile(std::filesystem::path path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Couldn't open file");

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}