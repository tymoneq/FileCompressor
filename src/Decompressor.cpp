#include "../include/Decompressor.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

Decompressor::Decompressor() {
    huffmanDecompressor();
    fileDecompressor();
}

Decompressor::~Decompressor() {}

void Decompressor::huffmanDecompressor() {
    ifstream file("huffman.bin", ios::binary);

    size_t keyCount = 0;
    file.read(reinterpret_cast<char*>(&keyCount), sizeof(keyCount));

    for (size_t i = 0; i < keyCount; i++) {
        char character;
        file.read(&character, sizeof(character));

        size_t codeLength;
        file.read(reinterpret_cast<char*>(&codeLength), sizeof(codeLength));

        string code(codeLength, '\0');
        file.read(&code[0], codeLength);

        this->keys[code] = character;
    }

    file.close();
}

void Decompressor::fileDecompressor() {
    ifstream inFile("compressed.bin", ios::binary);
    ofstream outFile("decompressed.txt");

    int bitCount = 0;
    inFile.read(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));

    int bytesCount = (bitCount + 7) / 8;

    vector<uint8_t> bytes(bytesCount);
    inFile.read(reinterpret_cast<char*>(bytes.data()), bytesCount);
    inFile.close();

    string bitString = "";

    for (size_t i = 0; i < bytes.size(); i++) {
        uint8_t byte = bytes[i];

        int bitsToTake = (i == bytes.size() - 1 && bitCount % 8 != 0 ? bitCount % 8 : 8);

        for (int j = 7; j >= 8 - bitsToTake; j--) bitString += ((byte >> j) & 1) ? '1' : '0';
    }
    string decodedText = "";
    string currentCode = "";

    for (const char& bit : bitString) {
        currentCode += bit;

        if (this->keys.find(currentCode) != this->keys.end()) {
            decodedText += keys[currentCode];
            currentCode = "";
        }
    }

    outFile << decodedText;

    outFile.close();
}