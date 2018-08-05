#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <deque>
#include <string>
#include "decode.h"

int main(int argc, char* argv[])
{
    std::ifstream codesStream(argv[1]);
    std::map<std::string, int> codes;
    int character, c, num_zeroes;
    std::string code;
    std::string bit_string = "";
    char input;
    while (codesStream >> character)
    {
        codesStream >> code;
        codes.insert(std::make_pair<std::string, int>(code, character));
    }

    std::ifstream inputStream("/dev/stdin", std::ios::binary);

    inputStream >> num_zeroes;
    while (inputStream >> std::noskipws >> input)
    {
        c = inputStream.peek();
        if (c == EOF)
        {
            if (inputStream.eof())
            {
                // last char
                for (int i = 0; i < 8 - num_zeroes; i++)
                {
                    bit_string.append(getBitI(input, i));
                    if (codes.count(bit_string) == 1)
                    {
                        // bit string matches decoding
                        std::cout << static_cast<char>(codes[bit_string]);
                        bit_string.clear();
                    }
                }
            }
            break;
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                bit_string.append(getBitI(input, i));
                if (codes.count(bit_string) == 1)
                {
                    // bit string matches decoding
                    std::cout << static_cast<char>(codes[bit_string]);
                    bit_string.clear();
                }
            }
        }
    }

    return 0;
}

std::string getBitI(char byte, int i)
{
    if ((byte << i) & 0x80)
    {
        return "1";
    }
    return "0";
}
