#include "rendertomHash.hpp"

string renderTomHash::text(const string &input) {
  const int prime = 1087;

  // https://werxltd.com/wp/2010/05/13/javascript-implementation-of-javas-string-hashcode-method/
  unsigned int seed = prime;
  for (char c : input) {
    seed = (seed << 5) - seed + c;
  }

  const string seedString = std::to_string(seed);
  const size_t seedStringSize = seedString.size();

  const string pattern = "0123456789abcdef";
  const size_t patternSize = pattern.size();

  string hash;
  unsigned int index = prime * seed;
  for (int i = 0; i < 64; i++) {
    index += seedString[i % seedStringSize] + i * prime;
    hash += pattern[index % patternSize];
  }
  return hash;
}