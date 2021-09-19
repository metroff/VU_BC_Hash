#include "file.hpp"

void genrateDataFiles() {
    std::string string = generateRandomWord(10000);
    genrateLongFile(string, "data/10000-1.txt");
    string = generateRandomWord(10000);
    genrateLongFile(string, "data/10000-2.txt");

    std::string outString = generateRandomWord(10000);
    std::string outString1 = "a" + outString;
    std::string outString2 = "b" + outString;
    genrateLongFile(outString1, "data/10000-a.txt.txt");
    genrateLongFile(outString2, "data/10000-b.txt");
}

void genrateLongFile(std::stringstream& stream, std::string filename) {
    std::ofstream output(filename);
    output << stream.rdbuf();
    output.close();
}

void genrateLongFile(std::string& out, std::string filename) {
    std::ofstream output(filename);
    output << out;
    output.close();
}

std::stringstream readFile(std::string filename) {
    std::stringstream sstream;
    std::ifstream input(filename);
    sstream << input.rdbuf();
    return sstream;
}