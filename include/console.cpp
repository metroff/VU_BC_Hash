#include "console.hpp"

// Clean command line
void clearLine() {
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Request integer from user
int getInt(std::string message, int low, int high) {
    int answer = -10;
    while (answer < low || answer > high) {
        std::cout << message;
        std::cin >> answer;
        if (std::cin.fail())
            clearLine();
    }
    clearLine();
    return answer;
}