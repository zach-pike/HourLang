#pragma once

#include <cstdint>
#include <sstream>

class MultiLineManager {
private:
    std::size_t indent = 0;
    std::stringstream ss;
public:
    MultiLineManager();
    ~MultiLineManager();

    void addIndentLevel();
    void removeIndentLevel();

    void insertIndent();

    void addText(std::string text);
    void addNewline();

    std::string getString() const;
};