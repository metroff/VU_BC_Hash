#include "file.hpp"

// Generate data files for first test
void genrateDataFiles() {
    std::string string = generateRandomWord(10000);
    genrateLongFile(string, "data/10000-1.txt");
    string = generateRandomWord(10000);
    genrateLongFile(string, "data/10000-2.txt");

    std::string outString = generateRandomWord(10000);
    std::string outString1 = "a" + outString;
    std::string outString2 = "b" + outString;
    genrateLongFile(outString1, "data/10000-a.txt");
    genrateLongFile(outString2, "data/10000-b.txt");
}

// File created using stringstream
void genrateLongFile(std::stringstream& stream, std::string filename) {
    std::ofstream output(filename);
    output << stream.rdbuf();
    output.close();
}
// File created using string
void genrateLongFile(std::string& out, std::string filename) {
    std::ofstream output(filename);
    output << out;
    output.close();
}

// Read from file to stringstream buffer
std::stringstream readFile(std::string filename) {
    std::stringstream sstream;
    std::ifstream input(filename);
    if (input) {
        sstream << input.rdbuf();
        return sstream;
    } else {
        std::cout << "File not found\n";
        usageText();
        exit(0);
    }
}

// Utilty usage message
void usageText() {
    std::string usage = "Usage:\n";
    usage += "./main <input_text>\n";
    usage += "./main -f <filepath>\n";
    usage += "./main -test";
    std::cout << usage << "\n";
}