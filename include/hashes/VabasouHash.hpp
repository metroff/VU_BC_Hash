#pragma once

#include "../myLib.hpp"

stringstream getText(const string &text);

string getTextAsString(const string &text);
namespace VabasouHash {
    string transformedText(const string &input);
}

string fileToHashCode(const string &text);