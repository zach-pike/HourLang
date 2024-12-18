#include "MultiLineManager.hpp"

MultiLineManager::MultiLineManager() {}
MultiLineManager::~MultiLineManager() {}

void MultiLineManager::addIndentLevel() {
    indent ++;
}

void MultiLineManager::removeIndentLevel() {
    indent --;
}

void MultiLineManager::insertIndent() {
    for (int i=0; i<indent; i++) ss << "  ";
}

void MultiLineManager::addText(std::string text) {
    ss << text;
}

void MultiLineManager::addNewline() {
    ss << '\n';
}

std::string MultiLineManager::getString() const {
    return ss.str();
}