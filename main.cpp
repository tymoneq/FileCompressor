#include <iostream>
#include <string>

#include "include/Huffman.h"

using namespace std;

int main() {
    string fileName = "test.txt";

    HuffmanTree huffmanTree;

    huffmanTree.createHuffmanTree(fileName);

    return 0;
}
