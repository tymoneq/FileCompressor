#ifndef DECOMPRESSOR
#define DECOMPRESSOR

#include <string>
#include <unordered_map>
using namespace std;

class Decompressor {
   private:
    unordered_map<string, char> keys;

   public:
    Decompressor();
    ~Decompressor();
    void huffmanDecompressor();
    void fileDecompressor();
};

#endif