#include <string>

struct Node
{
    int character;
    int freq;
    Node* left;
    Node* right;

    Node(): character(-1), freq(0), left(NULL), right(NULL) {}
    Node(int character, int freq): character(character), freq(freq), left(NULL), right(NULL) {}
};

void writeCodesToFile(Node* root, std::string path, int& compressedSize);
void writeCharCode(int character, std::string path);
void deleteEncoding(Node* root);
