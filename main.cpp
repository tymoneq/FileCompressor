#include <iostream>
#include <string>

#include "include/Decompressor.h"
#include "include/Huffman.h"

using namespace std;

int main() {
    string fileName = "test.txt";

    HuffmanTree huffmanTree(fileName);

    Decompressor decompressor;

    return 0;
}
