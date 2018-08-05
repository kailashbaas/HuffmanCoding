#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <deque>
#include <string>

char binary(int num);
std::string generateEncoding(std::deque<std::string>* binary_codes, int& current_bit_length);
int packCode(std::string& code);

int main(int argc, char* argv[])
{
    std::ifstream codesStream(argv[1]);
    std::map<int, std::string> codes;
    int character, extra_zeroes = 0;
    int current_bit_length = 0;
    std::string code, packed_code, binary_code;
    char input, binary_output;
    std::bitset<8> binary_packed_code;
    std::deque<std::string>* binary_codes = new std::deque<std::string>();
    std::deque<char> output_codes;
    while (codesStream >> character)
    {
        codesStream >> code;
        codes.insert(std::make_pair<int, std::string>(character, code));
    }

    std::ifstream inputStream("/dev/stdin", std::ios::binary);
    std::ofstream outputstream("/dev/stdout", std::ios::binary);

    while (inputStream >> std::noskipws >> input)
    {
        binary_code = codes[static_cast<int>(input)];
        current_bit_length += binary_code.length();
        binary_codes->push_back(binary_code);
        if (current_bit_length >= 8)
        {
            packed_code = generateEncoding(binary_codes, current_bit_length);
            binary_packed_code = std::bitset<8>(packed_code);
            binary_output = static_cast<char>(binary_packed_code.to_ulong());
            output_codes.push_back(binary_output);
        }
    }

    while (!binary_codes->empty())
    {
        packed_code = generateEncoding(binary_codes, current_bit_length);
        if (packed_code.length() < 8)
        {
            extra_zeroes = packCode(packed_code);
            //output_codes.push_front(static_cast<char>(extra_zeroes));
        }
        binary_packed_code = std::bitset<8>(packed_code);
        binary_output = static_cast<char>(binary_packed_code.to_ulong());
        output_codes.push_back(binary_output);
    }

    outputstream << extra_zeroes;
    while (!output_codes.empty())
    {
        outputstream << output_codes.front();
        output_codes.pop_front();
    }
    delete binary_codes;

    return 0;
}

char binary(int num)
{
    std::bitset<8> byte = std::bitset<8>(num);
    return static_cast<char>(byte.to_ulong());
}

std::string generateEncoding(std::deque<std::string>* binary_codes, int& current_bit_length)
{
    std::string packed_code = binary_codes->front();
    binary_codes->pop_front();
    while ((packed_code.length() != 8) && (!binary_codes->empty()))
    {
        if (packed_code.length() > 8)
        {
            current_bit_length = packed_code.substr(8).length();
            binary_codes->push_front(packed_code.substr(8));
            packed_code = packed_code.substr(0, 8);
        }
        else if ((!binary_codes->empty()) && (packed_code.length() < 8))
        {
            packed_code.append(binary_codes->front());
            binary_codes->pop_front();
            if (packed_code.length() == 8)
            {
                current_bit_length = 0;
            }
        }
    }
    /*if (packed_code.length() < 8)
    {
        packCode(packed_code);
    }*/
    if (packed_code.length() > 8)
    {
        current_bit_length = packed_code.substr(8).length();
        binary_codes->push_front(packed_code.substr(8));
        packed_code = packed_code.substr(0, 8);
    }
    return packed_code;
}

int packCode(std::string& code)
{
    int ret_val = 8 - code.length();
    for (int i = ret_val; i > 0; i--)
    {
        code += "0";
    }
    return ret_val;
}
