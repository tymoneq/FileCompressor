#ifndef HUFFMAN
#define HUFFMAN

#include <boost/dynamic_bitset.hpp>
#include <map>
#include <queue>
#include <string>
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
   public:
    HuffmanTree();
    ~HuffmanTree();
    void createHuffmanTree(const string& fileName);
    void createKeys(Node* currentNode);
    void dfs(Node* currentNode, bool val);
    void writeToBinary(const string& fileName);

   private:
    priority_queue<Node*, vector<Node*>, NodeComparator> pq;
    Node* root;
    boost::dynamic_bitset<> bitset;
    map<char, boost::dynamic_bitset<>> key;
};

#endif