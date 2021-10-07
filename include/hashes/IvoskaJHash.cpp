#include "IvoskaJHash.hpp"

int convertStringToUnsignedInt(string input) {
	const int init = 1773;
	const int magic = 7753;
    int stringConvertedToInt=0;
        stringConvertedToInt=stringConvertedToInt+init;
            for(int j = 0; j<63; j++){
                for (int i = 0; i < input.size(); i++) {
                    stringConvertedToInt = stringConvertedToInt + (input.at(i));
                    stringConvertedToInt = stringConvertedToInt * magic;
                    stringConvertedToInt = stringConvertedToInt - input.size();
                }
                stringConvertedToInt=stringConvertedToInt*init;
            }
	return stringConvertedToInt;
}

bitset<256> scrambleBits(bitset<256> &bs, int input){
    input = fabs(input);
    string sInput = to_string(input);
    for (int i = 0; i<sInput.length(); i++){
    bs = bs << 7;
    bs.flip();
    bs.set(i+sInput.length()*(input%2));
    bs.flip();
    bs.reset(sInput.length()/5);
    bs.flip();
    bs = bs << i;
    bs = bs >> (i+sInput.length()%3);
    bs = bs << (input&3);
    bs.flip();
    bs = bs >> (input%2);
    bs.flip();
    if(bs[256]=false){
    bs.set(255);
    }
    else{
        bs.reset(255);
        }
    }
    bs.flip();
    if(bs[0]=false){
        scrambleBits(bs, (input+7));
    }
    else if(bs[255]=false){
        scrambleBits(bs, (input-7753));
    }
    else if(bs[127]=false){
        scrambleBits(bs, ((input*3)+1729));
    }
    else if(bs[129]=false){
        scrambleBits(bs, (input-17));
    }
    else if(bs[130]=true){
        bs.reset(130);
        bs = bs >> 7;
    }
    return bs;
}

string returnedHexedBits(int input){
    bitset<256> bs(input^2);
    scrambleBits(bs, input);
    string stringedBits = bs.to_string();
    return stringedBits;
}

string toHash(int input) {
    bitset<256> bs(input^2);
    scrambleBits(bs, input);
	string temp;
	string stringedBits = bs.to_string();
	unsigned int b=0;
	for(int i = 0; i<64; i++){
        string stringedBits4="";
        for(int j = 0; j<4; j++){
            stringedBits4.push_back(stringedBits.back());
            stringedBits.pop_back();
        }
        int a = 0;
        a = a + (stringedBits4.at(0)-48)*8;
        a = a + (stringedBits4.at(1)-48)*4;
        a = a + (stringedBits4.at(2)-48)*2;
        a = a + (stringedBits4.at(3)-48)*1;
        stringstream ss;
        ss << hex << a;
        temp = temp+(ss.str());
	}
	return temp;
}

string IvoskaJHash::giveOutPut(string input) {
	string output;
	string out;
	stringstream ss;
    output = toHash(convertStringToUnsignedInt(input));
	return output;
}
