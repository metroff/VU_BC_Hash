#include "hash.hpp"

// unsigned int countSetBits(unsigned int n) {
//     unsigned int count = 0;
//     while (n) {
//         count += n & 1;
//         n >>= 1;
//     }
//     return count;
// }

std::string intToHex( unsigned int i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(unsigned int)*2) 
         << std::hex << i;
  return stream.str();
}

int leftRotate(int n, unsigned int d) {
    return (n << d)|(n >> (32 - d));
}

unsigned int rightRotate(unsigned int n, unsigned int d)
{
    return (n >> d)|(n << (32 - d));
}

std::string hash(std::string input) {
    std::string output;

    unsigned int hexes[8] = {3189621198, 405587210, 2844532716, 1761483275, 152458759, 2779224377, 4151057064, 1000842129};

    int length = input.length();

    int num = 1153;
    int sum = num;

    for (int i = 0; i < length; i++){
        // sum *= (int(input[i]) | int(input[i]) ^ sum);
        sum = num|(int(input[i])%num);
        num = leftRotate(num, 5) + int(input[i]) - num;
    }
    
    for (int i = 1; i < sum % 100; i++) {
         hexes[i%8] = rightRotate(hexes[i%8], 16);
    }

    // for (int i = 0; i < 4; i++) {
    //     hexes[i] = hexes[i]^hexes[7-i];
    //     hexes[7-i] = hexes[7-i]^(~hexes[i]);
    // }
    std::string numberasstring = std::to_string(num*num);
    int numLen = numberasstring.length();
    
    // for (int i = 0; i< 8; i++) {
    //     hexes[i] = (hexes[int(numberasstring[(i*2)%numLen])] | hexes[int(numberasstring[(i*2+1)%numLen])]);
    // }

    for (int i = 0; i < 8; i++) {

        hexes[i] ^= (~hexes[7-i]) * num;
        hexes[7-i] |= (~hexes[i]) * sum;
    }

    for (int i = 0; i < 8; i++) {
        output += intToHex(hexes[i]);//^(num*sum));
    }
    return output;
}