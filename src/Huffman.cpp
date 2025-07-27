#include "../include/Huffman.h"

#include <cmath>
#include <fstream>
#include <map>
#include <queue>
#include <string>

using namespace std;

Node* createNode(const char& character, const unsigned int& value, Node* leftSon, Node* rightSon) {
    Node* leaf = new Node();
    leaf->encodedChar = character;
    leaf->value = value;
    leaf->leftSon = leftSon;
    leaf->rightSon = rightSon;

    return leaf;
}

HuffmanTree::HuffmanTree() {}

HuffmanTree::~HuffmanTree() {}

void HuffmanTree::createHuffmanTree(const string& fileName) {
    ifstream file(fileName);
    string row;

    map<char, unsigned int> frequency;

    while (getline(file, row)) {
        for (const char& c : row)
            if (c > 0) frequency[c]++;
    }

    for (const auto& el : frequency) pq.push(createNode(el.first, el.second, nullptr, nullptr));

    // Build Huffman tree by combining nodes
    while (pq.size() > 1) {
        auto leftSon = pq.top();
        pq.pop();

        auto rightSon = pq.top();
        pq.pop();

        auto newNode = createNode('.', leftSon->value + rightSon->value, leftSon, rightSon);

        pq.push(newNode);
    }

    root = pq.top();
    pq.pop();
}
