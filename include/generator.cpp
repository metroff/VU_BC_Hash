#include "generator.hpp"

std::random_device device;
std::mt19937 rng(device());

// Integer generator
int generateIntInRange(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

// Word generator
std::string generateRandomWord(int length) {
    std::string output = "";
    // ASCII symbol array = string
    for (int i = 0; i<length; i++) {
         output += char(generateIntInRange(ASCII_CHAR_MIN, ASCII_CHAR_MAX));
    }
    return output;
}

// Word stream generator
std::stringstream generateStream(bool oneLetterDiff) {
    // Needed for normal printing
    bool firstLine = true;
    int length[4] = {10, 100, 500, 1000};
    std::stringstream output;
    // For loops for 100000 entries
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 25000; j++) {
            std::string first, second;
            // Check for needed data stream
            if (!oneLetterDiff) {
                first = generateRandomWord(length[i]);
                second = generateRandomWord(length[i]);
                while (first == second) {
                    second = generateRandomWord(length[i]); 
                }
            } else {
                first = generateRandomWord(length[i]-1);
                second = "b" + first;
                first = "a" + first;
            }
            
            if (firstLine) {
                output << first << " " << second;
                firstLine = false;
            } else {
                output << std::endl << first << " " << second;
            }
        }
    }
    return output;
}