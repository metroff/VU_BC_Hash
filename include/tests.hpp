#pragma once

#include "myLib.hpp"

void runTestWizard();
void runHashLengthAndDeterministicTests();
void benchmarkMyHash(const std::string&);
void benchmarkMultipleHashesLineByLine(const std::string&);
void benchmarkMultipleHashesWholeFile(const std::string&);
void testHashCollision();
void testHashOutputDifference();

void initTest(std::string, std::string filename = "", int iterations = 0);
std::string hexToBin(std::string);