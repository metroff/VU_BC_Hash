#include "main.hpp"

struct TestSubject {
    string name;
    double lineByLineTime = 0;
    double averageLineByLineTime = 0;
    double wholeFileTime = 0;
    double averageWholeFileTime = 0;
    int collisionCount = 0;
    double averageHexDifference = 0;
    double averageBitDifference = 0;
};

void initTestSubjects(TestSubject* subjects, int size) {
    string name;
    ifstream input("data/github.txt");
    for (int i = 0; i < size; i++) {
        input >> name;
        subjects[i].name = name;
    }
    input.close();
}

void printResults(TestSubject* subjects, int size) {
    ofstream output("rez.csv");
    std::cout << std::fixed << std::setprecision(6);
    output << std::fixed << std::setprecision(6);
    string outputStr = "Username, Line by line avg (ms), Whole File avg (ms), Collission count, Average Hex difference, Average Bit difference\n";
    cout << outputStr;
    output << outputStr; 
    
    for (int i = 0; i < size; i++)
    {
        cout << subjects[i].name << ", " 
        << subjects[i].averageLineByLineTime << ", " 
        << subjects[i].averageWholeFileTime << ", "
        << subjects[i].collisionCount << ", "
        << subjects[i].averageHexDifference << ", " << subjects[i].averageBitDifference << "\n";
        output << subjects[i].name << "," 
        << subjects[i].averageLineByLineTime << "," 
        << subjects[i].averageWholeFileTime << ","
        << subjects[i].collisionCount << ","
        << subjects[i].averageHexDifference << "," << subjects[i].averageBitDifference << "\n";
    }
    output.close();
}

///////////////////////////////////////////////////////////////////////
// Utility
///////////////////////////////////////////////////////////////////////
// Helper function for better console navigation
void initTest(std::string message, std::string filename = "", int iterations = 0) {
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
}

// Function for converting hex symbols (char) to binary (4 bit) as string
std::string _hexToBin(std::string input) {
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

///////////////////////////////////////////////////////////////////////
// Speed tests
///////////////////////////////////////////////////////////////////////


// Hashing one line at the time function with comparison to other algorithms
void benchmarkMultipleHashesLineByLine(const std::string& filename, TestSubject* subjects) {
    Timer timer;
    int timesRun = 5000;
    std::string line;

    initTest("Benchmark line by line hashing",filename,timesRun);

    std::stringstream input = readFile(filename);
    for (int i = 0; i < timesRun; i++) {
        while(getline(input, line)) {
            timer.reset();
            metroffHash::myHash(line);
            subjects[0].lineByLineTime += timer.elapsed();

            timer.reset();
            renderTomHash::text(line);
            subjects[1].lineByLineTime += timer.elapsed();

            timer.reset();
            MiautawnHash::my_hash(line);
            subjects[2].lineByLineTime += timer.elapsed();

            timer.reset();
            domas404Hash::hashfunc(line);
            subjects[3].lineByLineTime += timer.elapsed();

            timer.reset();
            IvoskaJHash::giveOutPut(line);
            subjects[4].lineByLineTime += timer.elapsed();

            timer.reset();
            OvidijusVHash::hashFunction(line);
            subjects[5].lineByLineTime += timer.elapsed();

            timer.reset();
            swoogieHash::hashFun(line);
            subjects[6].lineByLineTime += timer.elapsed();

            timer.reset();
            VabasouHash::transformedText(line);
            subjects[7].lineByLineTime += timer.elapsed();

            timer.reset();
            MantasM2001Hash::DuomenuHashinimas(line);
            subjects[8].lineByLineTime += timer.elapsed();

            timer.reset();
            EimantasVHash::Hash(line);
            subjects[9].lineByLineTime += timer.elapsed();
        }
    }

    for (int i = 0; i < 10; i++)
    {
        subjects[i].averageLineByLineTime = subjects[i].lineByLineTime * 1000 / timesRun;
    }

    std::cout << "Test end.\n-------\n\n";

    // std::string hashName[4] = {"MyHash", "md5", "sha1", "sha256"};

    // std::cout << std::fixed << std::setprecision(6);
    // for (int i = 0; i < 4; i++) {
    //     std::cout << hashName[i] << " total: " << timeTable[i] << " s.";
    //     std::cout << ", average: " << timeTable[i]*1000/timesRun << " ms.\n";
    // }
}

// Hashing whole file at the time function with comparison to other algorithms
void benchmarkMultipleHashesWholeFile(const std::string& filename, TestSubject* subjects) {
    Timer timer;
    int timesRun = 5000;

    initTest("Benchmark whole file hashing",filename,timesRun);

    std::stringstream input = readFile(filename);
    std::string line = input.str();

    for (int i = 0; i < timesRun; i++) {
        timer.reset();
        metroffHash::myHash(line);
        subjects[0].wholeFileTime += timer.elapsed();

        timer.reset();
        renderTomHash::text(line);
        subjects[1].wholeFileTime += timer.elapsed();

        timer.reset();
        MiautawnHash::my_hash(line);
        subjects[2].wholeFileTime += timer.elapsed();

        timer.reset();
        domas404Hash::hashfunc(line);
        subjects[3].wholeFileTime += timer.elapsed();

        timer.reset();
        IvoskaJHash::giveOutPut(line);
        subjects[4].wholeFileTime += timer.elapsed();

        timer.reset();
        OvidijusVHash::hashFunction(line);
        subjects[5].wholeFileTime += timer.elapsed();

        timer.reset();
        swoogieHash::hashFun(line);
        subjects[6].wholeFileTime += timer.elapsed();

        timer.reset();
        VabasouHash::transformedText(line);
        subjects[7].wholeFileTime += timer.elapsed();

        timer.reset();
        MantasM2001Hash::DuomenuHashinimas(line);
        subjects[8].wholeFileTime += timer.elapsed();
        
        timer.reset();
        EimantasVHash::Hash(line);
        subjects[9].wholeFileTime += timer.elapsed();
    }

    for (int i = 0; i < 10; i++)
    {
        subjects[i].averageWholeFileTime = subjects[i].wholeFileTime * 1000 / timesRun;
    }

    std::cout << "Test end.\n-------\n\n";
    // std::string hashName[4] = {"MyHash", "md5", "sha1", "sha256"};

    // std::cout << std::fixed << std::setprecision(6);
    // for (int i = 0; i < 4; i++) {
    //     std::cout << hashName[i] << " total: " << timeTable[i] << " s.";
    //     std::cout << ", average: " << timeTable[i]*1000/timesRun << " ms.\n";
    // }
}

///////////////////////////////////////////////////////////////////////
// Collision test
///////////////////////////////////////////////////////////////////////
// Tests for same hash output
void testHashCollision(TestSubject* subjects) {
    initTest("MyHash collision test");

    int collisions = 0;
    std::stringstream stream = generateStream();
    std::string first, second;
    while (!stream.eof()) {
        stream >> first >> second;
        // cout << function(first) << endl;
        if (metroffHash::myHash(first) == metroffHash::myHash(second)) {
            subjects[0].collisionCount++;
        }
        if (renderTomHash::text(first) == renderTomHash::text(second)) {
            subjects[1].collisionCount++;
        }
        if (MiautawnHash::my_hash(first) == MiautawnHash::my_hash(second)) {
            subjects[2].collisionCount++;
        }
        if (domas404Hash::hashfunc(first) == domas404Hash::hashfunc(second)) {
            subjects[3].collisionCount++;
        }
        if (IvoskaJHash::giveOutPut(first) == IvoskaJHash::giveOutPut(second)) {
            subjects[4].collisionCount++;
        }
        if (OvidijusVHash::hashFunction(first) == OvidijusVHash::hashFunction(second)) {
            subjects[5].collisionCount++;
        }
        if (swoogieHash::hashFun(first) == swoogieHash::hashFun(second)) {
            subjects[6].collisionCount++;
        }
        if (VabasouHash::transformedText(first) == VabasouHash::transformedText(second)) {
            subjects[7].collisionCount++;
        }
        if (MantasM2001Hash::DuomenuHashinimas(first) == MantasM2001Hash::DuomenuHashinimas(second)) {
            subjects[8].collisionCount++;
        }
        if (EimantasVHash::Hash(first) == EimantasVHash::Hash(second)) {
            subjects[9].collisionCount++;
        }
    }
    std::cout << "Test end.\n-------\n\n";
    // std::cout << "MyHash colision count: " << collisions << std::endl;
}

///////////////////////////////////////////////////////////////////////
// Hex, bit difference test
///////////////////////////////////////////////////////////////////////
template <typename F>
void differenceTestUtility(string& first, string&second, F function, TestSubject& subject) {
    string hashFirst, hashSecond, bitFirst, bitSecond;

    hashFirst = function(first);
    hashSecond = function(second);

    bitFirst = _hexToBin(hashFirst);
    bitSecond = _hexToBin(hashSecond);
    // Hex checking
    int notEqualHexCount = 0; 
    double hexCountPercentage = 0.0;

    for (int j = 0; j < 64; j++) {
        if (hashFirst[j] != hashSecond[j]) notEqualHexCount++;
    }

    hexCountPercentage = (notEqualHexCount / 64.0) * 100.0;
    subject.averageHexDifference += hexCountPercentage;
    // Bit checking
    int notEqualBitCount = 0; 
    double bitCountPercentage = 0.0;

    for (int j = 0; j < 256; j++) {
        if (bitFirst[j] != bitSecond[j]) notEqualBitCount++;
    }

    bitCountPercentage = (notEqualBitCount / 256.0) * 100.0;
    subject.averageBitDifference += bitCountPercentage;
}

// Calculated hash output hex and bit difference
void testHashOutputDifference(TestSubject* subjects) {
    initTest("MyHash output difference in bits and hex test");

    int lineCount = 100000;

    std::stringstream stream = generateStream(true);
    std::string first, second, hashFirst, hashSecond, bitFirst, bitSecond;

    for (int i = 0; i < lineCount; i++) {
        stream >> first >> second;

        differenceTestUtility(first, second, metroffHash::myHash, subjects[0]);
        differenceTestUtility(first, second, renderTomHash::text, subjects[1]);
        differenceTestUtility(first, second, MiautawnHash::my_hash, subjects[2]);
        differenceTestUtility(first, second, domas404Hash::hashfunc, subjects[3]);
        differenceTestUtility(first, second, IvoskaJHash::giveOutPut, subjects[4]);
        differenceTestUtility(first, second, OvidijusVHash::hashFunction, subjects[5]);
        differenceTestUtility(first, second, swoogieHash::hashFun, subjects[6]);
        differenceTestUtility(first, second, VabasouHash::transformedText, subjects[7]);
        differenceTestUtility(first, second, MantasM2001Hash::DuomenuHashinimas, subjects[8]);
        differenceTestUtility(first, second, EimantasVHash::Hash, subjects[9]);
    }

    for (int i = 0; i < 10; i++)
    {
        subjects[i].averageHexDifference /= lineCount;
        subjects[i].averageBitDifference /= lineCount;
    }
    std::cout << "Test end.\n-------\n\n";
}

int main() {
    const int subjectCount = 10;
    TestSubject testSubjects[subjectCount];
    initTestSubjects(testSubjects, subjectCount);
    benchmarkMultipleHashesLineByLine("data/konstitucija.txt", testSubjects);
    benchmarkMultipleHashesWholeFile("data/konstitucija.txt", testSubjects);
    testHashCollision(testSubjects);
    testHashOutputDifference(testSubjects);
    printResults(testSubjects, subjectCount);
    // string line;
    // stringstream stream = generateStream();
    // while(stream >> line) {
    //     cout << MantasM2001Hash::DuomenuHashinimas(line) << "\n";
    // }
}