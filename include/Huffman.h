#ifndef HUFFMAN
#define HUFFMAN

#include <map>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    unsigned int value = 0;
    char encodedChar;  // only for leaves
    Node* leftSon;
    Node* rightSon;
};

Node* createNode(const char& character, const unsigned int& value, Node* leftSon, Node* rightSon);

struct NodeComparator {
    bool operator()(const Node* lhs, const Node* rhs) const { return lhs->value > rhs->value; }
};

class HuffmanTree {
   private:
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;
    Node* root;
    string bitSet;
    unordered_map<char, string> key;

   public:
    HuffmanTree(const string& fileName);
    ~HuffmanTree();
    void createHuffmanTree(const string& fileName);
    void createKeys(Node* currentNode);
    void dfs(Node* currentNode, char val);
    void writeToBinary(const string& fileName);
    void writeHuffmanToBinary();
    void createBinary(const string& fileName, const string& bitString);
    vector<uint8_t> toBytes(int& bitCount, const string& bitString);
};

#endif