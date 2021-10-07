#include "VabasouHash.hpp"

stringstream getText(const string &text) {
    std::ifstream file;
    file.open(text);

    if(!file) {
        throw std::runtime_error("File could not be opened");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer;
}

string getTextAsString(const string &text) {
    stringstream buffer = getText(text);
    string content = buffer.str();
    return content;
}

string VabasouHash::transformedText(const string &input) {
    const int main = 1097;

    unsigned int seed = main;
    for (char c : input) {
    seed = (seed << 7) - seed + int(c) + 47 * input.length();
    }

    string seedString = std::to_string(seed);
    int seedStringSize = seedString.size();

    string pattern = "0123456789abcdef";
    int patternSize = pattern.size();

    string hash;
    int changingNumber = 31;
    unsigned int index = main * seed;
    for (int i = 0; i < 64; i++) {
        index += seedString[changingNumber % seedStringSize] + i * main / (main & 5);
        hash += pattern[index % patternSize];
        changingNumber++;
    }
    return hash;
}

string fileToHashCode(const string &text) {
    string content = getTextAsString(text);
    string hash = VabasouHash::transformedText(content);

    return hash;
}
