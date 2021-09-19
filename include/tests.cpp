#include "tests.hpp"
#include "hash.hpp"
#include "file.hpp"
#include "timer.hpp"
#include "console.hpp"
#include "md5.hpp"
#include "sha1.hpp"
#include "sha256.hpp"

// Main test wizard with all selectable options
void runTestWizard() {
    std::string output = "1: Hash output length, deterministic algorithm test\n";
    output += "2: Benchmark line by line hashing (MyHash)\n";
    output += "3: Benchmark line by line hashing (MyHash, md5, sha1, sha256)\n";
    output += "4: Benchmark whole file hashing (MyHash, md5, sha1, sha256)\n";
    output += "5: MyHash collision test\n";
    output += "6: MyHash output difference in bits and hex test\n";
    output += "Select: ";
    
    // Choice panel
    int command = getInt(output, 1, 6);
    switch(command) {
        case 1: runHashLengthAndDeterministicTests(); break;
        case 2: benchmarkMyHash("data/konstitucija.txt"); break;
        case 3: benchmarkMultipleHashesLineByLine("data/konstitucija.txt"); break;
        case 4: benchmarkMultipleHashesWholeFile("data/konstitucija.txt"); break;
        case 5: testHashCollision(); break;
        case 6: testHashOutputDifference(); break;
        default: std::cout << output << std::endl; break;
    }
}

///////////////////////////////////////////////////////////////////////
// Deterministic, length tests
///////////////////////////////////////////////////////////////////////
// Check if hash is deterministic run loop 100 times
bool isHashDeterministic(const std::string& input, std::string filename) {
    std::string hashText = myHash(input);
    for (int i = 0; i < 100; i++) {
        if (hashText != myHash(input)) {
            // std::cout << "File '" << filename << "' hashes are not the same.\n";
            return false;
        }
    }
    // std::cout << "File '" << filename << "' hashes are the same.\n";
    return true;
}

// Check if hash output length does not change run loop 100 times
bool testHashLength(const std::string& input, std::string filename) {
    std::string hashString;
    for (int i = 0; i < 100; i++) {
        hashString = myHash(input);
        if (hashString.length() != 64) {
            // std::cout << "File '" << filename << "' hash length is not 64!\n";
            return false;
        }
    }
    // std::cout << "File '" << filename << "' hash length is 64!\n";
    std::cout << filename << " HASH: " << hashString << "\n";
    return true;
}

// Function for tests above
void runHashLengthAndDeterministicTests() {
    initTest("Hash output length, deterministic algorithm test");

    bool flag1 = true, flag2 = true;
    std::string file_names[7] = {"empty.txt", "a.txt", "b.txt", "10000-1.txt", "10000-2.txt", "10000-a.txt", "10000-b.txt"};

    genrateDataFiles();

    for (int i = 0; i < 7; i++) {
        std::string filename = "data/" + file_names[i];
        flag1 = testHashLength(readFile(filename).str(), filename);
        if (!flag1) break;
    }

    for (int i = 0; i < 7; i++) {
        std::string filename = "data/" + file_names[i];
        flag2 = isHashDeterministic(readFile(filename).str(), filename);
        if (!flag2) break;
    }

    std::cout << "\n";
    if (flag1) {
        std::cout << "Length of hash function output is always the same!\n";
    } else {
        std::cout << "Length of hash function output is not the same!\n";
    }

    if (flag2) {
        std::cout << "Hash function is deterministic!\n";
    } else {
        std::cout << "Hash function is not deterministic!\n";
    }
}

///////////////////////////////////////////////////////////////////////
// Speed tests
///////////////////////////////////////////////////////////////////////
// Hashing one line at the time function
void benchmarkMyHash(const std::string& filename) {
    Timer timer;
    double totalHashTime = 0;
    int timesRun = 5000;
    std::string line;

    initTest("Benchmark line by line hashing (MyHash)",filename,timesRun);

    std::stringstream input = readFile(filename);
    for (int i = 0; i < timesRun; i++) {
        while(getline(input, line)) {
            timer.reset();
            myHash(line);
            totalHashTime += timer.elapsed();
        }
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "MyHash total time: " << totalHashTime << " s.\n";
    std::cout << "MyHash average time per run: " << (totalHashTime*1000)/timesRun << " ms.\n";
}

// Hashing one line at the time function with comparison to other algorithms
void benchmarkMultipleHashesLineByLine(const std::string& filename) {
    Timer timer;
    double timeTable[4] = {0};
    int timesRun = 5000;
    std::string line;

    initTest("Benchmark line by line hashing (MyHash, md5, sha1, sha256)",filename,timesRun);

    std::stringstream input = readFile(filename);
    for (int i = 0; i < timesRun; i++) {
        while(getline(input, line)) {
            timer.reset();
            myHash(line);
            timeTable[0] += timer.elapsed();

            timer.reset();
            md5(line);
            timeTable[1] += timer.elapsed();

            timer.reset();
            sha1(line);
            timeTable[2] += timer.elapsed();

            timer.reset();
            sha256(line);
            timeTable[3] += timer.elapsed();
        }
    }

    std::string hashName[4] = {"MyHash", "md5", "sha1", "sha256"};

    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < 4; i++) {
        std::cout << hashName[i] << " total: " << timeTable[i] << " s.";
        std::cout << ", average: " << timeTable[i]*1000/timesRun << " ms.\n";
    }
}

// Hashing whole file at the time function with comparison to other algorithms
void benchmarkMultipleHashesWholeFile(const std::string& filename) {
    Timer timer;
    double timeTable[4] = {0};
    int timesRun = 5000;

    initTest("Benchmark whole file hashing (MyHash, md5, sha1, sha256)",filename,timesRun);

    std::stringstream input = readFile(filename);
    std::string line = input.str();

    for (int i = 0; i < timesRun; i++) {
        timer.reset();
        myHash(line);
        timeTable[0] += timer.elapsed();

        timer.reset();
        md5(line);
        timeTable[1] += timer.elapsed();

        timer.reset();
        sha1(line);
        timeTable[2] += timer.elapsed();

        timer.reset();
        sha256(line);
        timeTable[3] += timer.elapsed();
    }

    std::string hashName[4] = {"MyHash", "md5", "sha1", "sha256"};

    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < 4; i++) {
        std::cout << hashName[i] << " total: " << timeTable[i] << " s.";
        std::cout << ", average: " << timeTable[i]*1000/timesRun << " ms.\n";
    }
}

///////////////////////////////////////////////////////////////////////
// Collision test
///////////////////////////////////////////////////////////////////////
// Tests for same hash output
void testHashCollision() {
    initTest("MyHash collision test");

    int collisions = 0;
    std::stringstream stream = generateStream();
    std::string first, second;
    while (!stream.eof()) {
        stream >> first >> second;
        if (myHash(first) == myHash(second)) {
            collisions++;
        }
    }
    std::cout << "MyHash colision count: " << collisions << std::endl;
}

///////////////////////////////////////////////////////////////////////
// Hex, bit difference test
///////////////////////////////////////////////////////////////////////
// Calculated hash output hex and bit difference
void testHashOutputDifference() {
    initTest("MyHash output difference in bits and hex test");

    double hexMin = 100.0, hexMax = 0.0, hexAvg = 0.0;
    double bitMin = 100.0, bitMax = 0.0, bitAvg = 0.0;
    int lineCount = 100000;

    std::stringstream stream = generateStream(true);
    std::string first, second, hashFirst, hashSecond, bitFirst, bitSecond;

    for (int i = 0; i < lineCount; i++) {
        stream >> first >> second;

        hashFirst = myHash(first);
        hashSecond = myHash(second);

        bitFirst = hexToBin(hashFirst);
        bitSecond = hexToBin(hashSecond);
        // Hex checking
        int notEqualHexCount = 0; 
        double hexCountPercentage = 0.0;

        for (int j = 0; j < 64; j++) {
            if (hashFirst[j] != hashSecond[j]) notEqualHexCount++;
        }

        hexCountPercentage = (notEqualHexCount / 64.0) * 100.0;
        if (hexMin > hexCountPercentage) hexMin = hexCountPercentage;
        if (hexMax < hexCountPercentage) hexMax = hexCountPercentage;
        hexAvg += hexCountPercentage;
        // Bit checking
        int notEqualBitCount = 0; 
        double bitCountPercentage = 0.0;

        for (int j = 0; j < 256; j++) {
            if (bitFirst[j] != bitSecond[j]) notEqualBitCount++;
        }

        bitCountPercentage = (notEqualBitCount / 256.0) * 100.0;
        if (bitMin > bitCountPercentage) bitMin = bitCountPercentage;
        if (bitMax < bitCountPercentage) bitMax = bitCountPercentage;
        bitAvg += bitCountPercentage;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Hex max difference: " << "hex: " << std::setw(6) << hexMax << " %" 
        << ", bit: " << std::setw(6) << bitMax << " %\n";
    std::cout << "Hex avg difference: " << "hex: " << std::setw(6) << hexAvg / lineCount << " %" 
        << ", bit: " << std::setw(6) << bitAvg / lineCount << " %\n";
    std::cout << "Hex min difference: " << "hex: " << std::setw(6) << hexMin << " %" 
        << ", bit: " << std::setw(6) << bitMin << " %\n";
}

///////////////////////////////////////////////////////////////////////
// Utility
///////////////////////////////////////////////////////////////////////
// Helper function for better console navigation
void initTest(std::string message, std::string filename, int iterations) {
    std::cout << "-------\n";
    if(message != "") {
        std::cout << "Running: " << message << "\n";
    }
    if(filename != "") {
        std::cout << "Input file: " << filename << "\n";
    }
    if(iterations != 0) {
        std::cout << "Number of iterations: " << iterations << "\n";
    }
    std::cout << "-------\n\n";
}

// Function for converting hex symbols (char) to binary (4 bit) as string
std::string hexToBin(std::string input) {
    int i = 0;
    std::string output = "";
    while (input[i]) {
        switch (input[i]) {
        case '0':
            output += "0000";
            break;
        case '1':
            output += "0001";
            break;
        case '2':
            output += "0010";
            break;
        case '3':
            output += "0011";
            break;
        case '4':
            output += "0100";
            break;
        case '5':
            output += "0101";
            break;
        case '6':
            output += "0110";
            break;
        case '7':
            output += "0111";
            break;
        case '8':
            output += "1000";
            break;
        case '9':
            output += "1001";
            break;
        case 'A':
        case 'a':
            output += "1010";
            break;
        case 'B':
        case 'b':
            output += "1011";
            break;
        case 'C':
        case 'c':
            output += "1100";
            break;
        case 'D':
        case 'd':
            output += "1101";
            break;
        case 'E':
        case 'e':
            output += "1110";
            break;
        case 'F':
        case 'f':
            output += "1111";
            break;
        default:
            std::cout << "\nInvalid hexadecimal digit "
                 << input[i] << std::endl;
        }
        i++;
    }
    return output;
}