#include "../include/Huffman.h"

#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <cmath>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

Node* createNode(const char& character, const unsigned int& value, Node* leftSon, Node* rightSon) {
    Node* leaf = new Node();
    leaf->encodedChar = character;
    leaf->value = value;
    leaf->leftSon = leftSon;
    leaf->rightSon = rightSon;
    return leaf;
}

HuffmanTree::HuffmanTree(const string& fileName) {
    createHuffmanTree(fileName);
    writeToBinary(fileName);
    writeHuffmanToBinary();
}

HuffmanTree::~HuffmanTree() {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(this->root);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->leftSon != nullptr) q.push(v->leftSon);

        if (v->rightSon != nullptr) q.push(v->rightSon);

        delete v;
    }

    this->root = nullptr;
}

void HuffmanTree::createHuffmanTree(const string& fileName) {
    ifstream file(fileName);
    string row;

    map<char, unsigned int> frequency;

    while (getline(file, row)) {
        for (const char& c : row)
            if (c > 0) frequency[c]++;

        frequency['\n']++;
    }
    file.close();

    for (const auto& el : frequency) pq.push(createNode(el.first, el.second, nullptr, nullptr));

    // Build Huffman tree by combining nodes
    while (pq.size() > 1) {
        auto leftSon = pq.top();
        pq.pop();

        auto rightSon = pq.top();
        pq.pop();

        auto newNode = createNode('~', leftSon->value + rightSon->value, leftSon, rightSon);

        pq.push(newNode);
    }

    root = pq.top();
    pq.pop();

    createKeys(root);
}

void HuffmanTree::dfs(Node* currentNode, char val) {
    bitSet.push_back(val);
    createKeys(currentNode);
    bitSet.pop_back();
}

void HuffmanTree::createKeys(Node* currentNode) {
    // check if leaf
    if (currentNode->leftSon == nullptr && currentNode->rightSon == nullptr)
        this->key[currentNode->encodedChar] = this->bitSet;

    if (currentNode->leftSon != nullptr) dfs(currentNode->leftSon, '0');

    if (currentNode->rightSon != nullptr) dfs(currentNode->rightSon, '1');
}
void HuffmanTree::writeToBinary(const string& fileName) {
    string row;
    ifstream file(fileName);

    string bitString = "";

    while (getline(file, row)) {
        for (const char& c : row)
            if (c > 0 && this->key.find(c) != this->key.end()) bitString.append(this->key[c]);

        if (this->key.find('\n') != this->key.end()) bitString.append(this->key['\n']);
    }
    file.close();

    // converting bits to bytes
    createBinary("compressed.bin", bitString);
}
void HuffmanTree::writeHuffmanToBinary() {
    ofstream outFile("huffman.bin", ios::binary);

    // Write the number of key-value pairs first
    size_t keyCount = key.size();
    outFile.write(reinterpret_cast<const char*>(&keyCount), sizeof(keyCount));

    for (const auto& el : this->key) {
        // Write the character
        char character = el.first;
        outFile.write(&character, sizeof(character));

        // Write the length of the Huffman code
        size_t codeLength = el.second.length();
        outFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));

        // Write the Huffman code as string
        outFile.write(el.second.c_str(), codeLength);
    }

    outFile.close();
}
void HuffmanTree::createBinary(const string& fileName, const string& bitString) {
    int bitCount = 0;
    vector<uint8_t> bytes = toBytes(bitCount, bitString);

    ofstream outFile(fileName, ios::binary);

    // writing number of bits encoded
    outFile.write(reinterpret_cast<const char*>(&bitCount), sizeof(bitCount));
    // writing bytes
    outFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());

    outFile.close();
}

vector<uint8_t> HuffmanTree::toBytes(int& bitCount, const string& bitString) {
    vector<uint8_t> bytes;
    uint8_t currentByte = 0;

    for (const char& bit : bitString) {
        currentByte = (currentByte << 1) | (bit == '1' ? 1 : 0);
        bitCount++;
        if (bitCount % 8 == 0) {
            bytes.emplace_back(currentByte);
            currentByte = 0;
        }
    }

    if (bitCount % 8 != 0) {
        currentByte <<= (8 - (bitCount % 8));
        bytes.emplace_back(currentByte);
    }

    return bytes;
}
