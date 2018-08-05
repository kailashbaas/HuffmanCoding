#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "huffman.h"


struct NodeComparator
{
    bool operator()(const Node* l, const Node* r) const
    {
        return l->freq > r->freq;
    }
};


int main()
{
    std::ifstream inputStream("/dev/stdin", std::ios::binary);
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> minHeap;
    int character;
    int freq;
    Node* temp = NULL;
    Node* root = NULL;
    Node* left;
    Node* right;
    Node* tree;

    while (inputStream >> character)
    {
        // process input
        inputStream >> freq;
        temp = new Node(character, freq);
        minHeap.push(temp);
    }

    while (minHeap.size() > 1)
    {
        // build encoding tree
        // following four lines, especially line creating right, may have to be changed
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        root = new Node(-1, left->freq + right->freq);
        root->left = left;
        root->right = right;
        minHeap.push(root);
    }
    tree = minHeap.top();

    int compressedSize = 0;
    writeCodesToFile(tree, "", compressedSize);
    std::cout << compressedSize << std::endl;
    deleteEncoding(tree);

    return 0;
}

void deleteEncoding(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        deleteEncoding(root->left);
        deleteEncoding(root->right);
        delete root;
        return;
    }
}

void writeCodesToFile(Node* root, std::string path, int& compressedSize)
{
    if (root == NULL)
    {
        return;
    }
    else if ((root->left == NULL) && (root->right == NULL))
    {
        writeCharCode(root->character, path);
        compressedSize += (root->freq * path.length());
        return;
    }
    else
    {
        std::string leftpath = path + "0";
        std::string rightpath = path + "1";
        writeCodesToFile(root->left, leftpath, compressedSize);
        writeCodesToFile(root->right, rightpath, compressedSize);
        return;
    }
}

void writeCharCode(int character, std::string path)
{
    std::ofstream outputstream;
    outputstream.open("./codewords.txt", std::ofstream::app);
    outputstream << character << '\t' << path << '\n';
    outputstream.close();
}
