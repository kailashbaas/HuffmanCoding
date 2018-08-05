#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::ifstream inputStream("/dev/stdin", std::ios::binary);
    char input;
    std::map<char, int> frequencies;
    int count = 1;
    while (inputStream >> std::noskipws >> input)
    {
        count = 1;
        if (frequencies.count(input) == 1)
        {
            // input already exists
            count = frequencies[input] + 1;
            frequencies.erase(input);
        }
        frequencies.insert(std::make_pair<char, int>(input, count));
    }

    for (std::map<char, int>::iterator i = frequencies.begin(); i != frequencies.end(); i++)
    {
        std::cout << static_cast<int>(i->first) << '\t' << i->second << '\n';
    }

    return 0;
}
