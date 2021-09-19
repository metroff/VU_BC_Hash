#pragma once

#include "myLib.hpp"

void runTestWizard();
void runHashLengthAndDeterministicTests();
void benchmarkMyHash();
void benchmarkMultipleHashesLineByLine(const std::string&);
void benchmarkMultipleHashesWholeFile(const std::string&);
void testHashCollision(std::stringstream);