#include "MultiLineManager.hpp"

MultiLineManager::MultiLineManager(std::ostream& _os):
    os(_os) {}
MultiLineManager::~MultiLineManager() {}

void MultiLineManager::addIndentLevel() {
    indent ++;
}

void MultiLineManager::removeIndentLevel() {
    indent --;
}

void MultiLineManager::insertIndent() {
    for (int i=0; i<indent; i++) os << "  ";
}

void MultiLineManager::addText(std::string text) {
    os << text;
}

void MultiLineManager::addNewline() {
    os << '\n';
}

std::size_t MultiLineManager::getIndentLevel() const {
    return indent;
}