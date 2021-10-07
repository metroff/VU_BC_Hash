#include "swoogieHash.hpp"

string swoogieHash::hashFun(string str){

    static const int primeInt = 7103;
    unsigned int hash = primeInt;
    for(int i=0; i<str.length(); ++i){
        hash = (hash*31) + int(str[i]);
    }

    string hashStr = std::to_string(hash);
    int hashStrSize = hashStr.size();

    unsigned int index = hash;
    static const string hex = "0123456789abcdef";
    string hexHash;

    for(int i=0; i<64; i++){
        index += int(hashStr[i % hashStrSize]) + i*primeInt*31;
        hexHash += hex[index % 16];
    }
    //cout << hexHash << std::endl;
    return hexHash;
}