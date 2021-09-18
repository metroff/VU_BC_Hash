#include "output.hpp"

void genrateDataFiles() {
    std::stringstream stream = generateStream();
    genrateLongFile(stream, "data/long1.txt");
    stream = generateStream();
    genrateLongFile(stream, "data/long2.txt");

    std::string outString = generateStream().str();
    genrateLongFile(outString, "data/longOneDiff1.txt", "a");
    genrateLongFile(outString, "data/longOneDiff2.txt", "b");
}

void genrateLongFile(std::stringstream& stream, std::string filename) {
    std::ofstream output(filename);
    output << stream.rdbuf();
    output.close();
}

void genrateLongFile(std::string& out, std::string filename, std::string stringToAdd) {
    std::ofstream output(filename);
    output << out << stringToAdd;
    output.close();
}

std::stringstream readFile(std::string filename) {
    std::stringstream sstream;
    std::ifstream input(filename);
    sstream << input.rdbuf();
    return sstream;
}