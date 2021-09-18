#pragma once

#include "myLib.hpp"
#include "generator.hpp"

void genrateDataFiles();
void genrateLongFile(std::stringstream&, std::string);
void genrateLongFile(std::string&, std::string, std::string);

std::stringstream readFile(std::string);
