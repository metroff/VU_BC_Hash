#include "tests.hpp"
#include "hash.hpp"
#include "file.hpp"
#include "timer.hpp"
#include "console.hpp"
#include "md5.hpp"
#include "sha1.hpp"
#include "sha256.hpp"

void runTestWizard() {
    std::string output = "1: Test if hash function is deterministic and output length is always the same\n";
    output += "2: Benchmark line by line hashing (MyHash)\n";
    output += "3: Benchmark line by line hashing (MyHash, md5, sha1, sha256)\n";
    output += "4: Benchmark whole file hashing (MyHash, md5, sha1, sha256)\n";
    output += "5: Test MyHash collision count\n";
    output += "Select: ";
    
    // Choice panel
    int command = getInt(output, 1, 5);
    switch(command) {
        case 1: runHashLengthAndDeterministicTests(); break;
        case 2: benchmarkMyHash(); break;
        case 3: benchmarkMultipleHashesLineByLine("data/konstitucija.txt"); break;
        case 4: benchmarkMultipleHashesWholeFile("data/konstitucija.txt"); break;
        case 5: testHashCollision(generateStream()); break;
        default: std::cout << output << std::endl; break;
    }
}

///////////////////////////////////////////////////////////////////////
// Deterministic, length tests
///////////////////////////////////////////////////////////////////////
bool isHashDeterministic(const std::string& input, std::string filename) {
    std::string hashText = hash(input);
    for (int i = 0; i < 100; i++) {
        if (hashText != hash(input)) {
            std::cout << "File '" << filename << "' hashes are not the same.\n";
            return false;
        }
    }
    std::cout << "File '" << filename << "' hashes are the same.\n";
    return true;
}

bool testHashLength(const std::string& input, std::string filename) {
    std::string hashString;
    for (int i = 0; i < 100; i++) {
        hashString = hash(input);
        if (hashString.length() != 64) {
            std::cout << "File '" << filename << "' hash length is not 64!\n";
            return false;
        }
    }
    std::cout << "File '" << filename << "' hash length is 64!\n";
    return true;
}

void runHashLengthAndDeterministicTests() {
    bool flag1 = true, flag2 = true;
    std::string file_names[7] = {"empty.txt", "a.txt", "b.txt", "long1.txt", "long2.txt", "longOneDiff1.txt", "longOneDiff2.txt"};

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

    if (flag1) {
        std::cout << "Length of hash function output is always 64!\n";
    } else {
        std::cout << "Length of hash function output is not 64!\n";
    }

    if (flag2) {
        std::cout << "Hash function is deterministic!\n";
    } else {
        std::cout << "Hash function is not deterministic!\n";
    }

    testHashCollision(generateStream());
}

///////////////////////////////////////////////////////////////////////
// Speed tests
///////////////////////////////////////////////////////////////////////

void benchmarkMyHash() {
    Timer timer;
    double totalHashTime = 0;
    int timesRun = 5000;
    std::string line;

    std::stringstream input = readFile("data/konstitucija.txt");
    for (int i = 0; i < timesRun; i++) {
        while(getline(input, line)) {
            timer.reset();
            hash(line);
            totalHashTime += timer.elapsed();
        }
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Total time: " << totalHashTime << " s.\n";
    std::cout << "Average time per run: " << totalHashTime*1000/timesRun << " ms.\n";
}

void benchmarkMultipleHashesLineByLine(const std::string& filename) {
    Timer timer;
    double timeTable[4] = {0};
    int timesRun = 5000;
    std::string line;

    std::stringstream input = readFile(filename);
    for (int i = 0; i < timesRun; i++) {
        while(getline(input, line)) {
            timer.reset();
            hash(line);
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

void benchmarkMultipleHashesWholeFile(const std::string& filename) {
    Timer timer;
    double timeTable[4] = {0};
    int timesRun = 5000;

    std::stringstream input = readFile(filename);
    std::string line = input.str();

    for (int i = 0; i < timesRun; i++) {
        timer.reset();
        hash(line);
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

void testHashCollision(std::stringstream stream) {
    int collisions = 0;
    std::string first, second;
    while (!stream.eof()) {
        stream >> first >> second;
        if (hash(first) == hash(second)) {
            collisions++;
        }
    }
    std::cout << "MyHash colision count: " << collisions << std::endl;
}

///////////////////////////////////////////////////////////////////////
// Collision test
///////////////////////////////////////////////////////////////////////