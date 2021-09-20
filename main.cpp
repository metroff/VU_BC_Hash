#include "include/myLib.hpp"
#include "include/file.hpp"
#include "include/hash.hpp"
#include "include/tests.hpp"

int main(int argc, char** argv) {
    if (argc == 2) {
        std::string input = argv[1];
        if (input == "-test") {
            runTestWizard();
        } else {
            std::cout << "HASH: " << myHash(input) << "\n";
        }
    } else if (argc == 3) {
        std::string command = argv[1];
        if (command == "-f") {
            std::string filename = argv[2];
            std::string fileInput = readFile(filename).str();
            std::cout << "HASH: " << myHash(fileInput) << "\n";
        } else {
            usageText();
        }
    } else usageText();
}

