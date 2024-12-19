#pragma once

#include <cstdint>
#include <sstream>

class MultiLineManager {
private:
    std::size_t indent = 0;
    std::ostream& os;
public:
    MultiLineManager(std::ostream& os);
    ~MultiLineManager();

    void addIndentLevel();
    void removeIndentLevel();

    void insertIndent();

    void addText(std::string text);
    void addNewline();

    std::size_t getIndentLevel() const;
};