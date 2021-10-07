#include "EimantasVHash.hpp"

std::string EimantasVHash::Hash(std::string inp)
{
    if (inp=="")inp="absdthu45th389wi";
    char hash[64] = {(char)0};
    for (int a = 0; a < inp.length(); a++)
    {
        for (int i = 0; i < 64; i++)
        {
            switch (((int)inp[a] + i + a) % 15)
            {
            case 0:
                hash[i] ^= inp[a];
                break;
            case 1:
                hash[i] ^= (inp[a] >> 2);
                break;
            case 2:
                hash[i] ^= (inp[a] >> 1);
                break;
            case 3:
                hash[i] ^= (inp[a] << 2);
                break;
            case 4:
                hash[i] ^= (inp[a] << 1);
                break;
            case 5:
                hash[i] ^= (~inp[a]);
                break;
            case 6:
                hash[i] ^= (~inp[a] << 1);
                break;
            case 7:
                hash[i] ^= (~inp[a] >> 1);
                break;
            case 8:
                hash[i] ^= (~inp[a] >> 2);
                break;
            case 9:
                hash[i] ^= (~inp[a] >> 3);
                break;
            case 10:
                hash[i] ^= (~inp[a] << 2);
                break;
            case 11:
                hash[i] ^= (~inp[a] << 3);
                break;
            case 12:
                hash[i] ^= (~inp[a] >> 1 << 1);
                break;
            case 13:
                hash[i] ^= (~inp[a] >> 2 << 2);
                break;
            case 14:
                hash[i] ^= (~inp[a] >> 3 << 3);
                break;
            }
        }
    }

    std::string out = "";
    // if (isBinary)
    // {
    //     for (int i = 0; i < 64; i++) // convert to hex
    //     {
    //         int t = ((int)hash[i]) / 16 + 8;
    //         //cout << (t&1) << endl;
    //         if((t&8)>0)
    //         {
    //             out += '1';
    //         }
    //         else
    //         {
    //             out += '0';
    //         }
    //         if((t&4)>0)
    //         {
    //             out += '1';
    //         }
    //         else
    //         {
    //             out += '0';
    //         }
    //         if((t&2)>0)
    //         {
    //             out += '1';
    //         }
    //         else
    //         {
    //             out += '0';
    //         }
    //         if((t&1)>0)
    //         {
    //             out += '1';
    //         }
    //         else
    //         {
    //             out += '0';
    //         }
    //     }

    // }
    // else
    // {

    for (int i = 0; i < 64; i++) // convert to hex
    {
        int t = ((int)hash[i]) / 16 + 8;

        if (t < 10)
            out += (char)(t + 48);
        else
        {
            switch (t)
            {
            case 10:
                out += 'a';
                break;
            case 11:
                out += 'b';
                break;
            case 12:
                out += 'c';
                break;
            case 13:
                out += 'd';
                break;
            case 14:
                out += 'e';
                break;
            case 15:
                out += 'f';
                break;
            }
        }
    }
    // }
    return out;
}