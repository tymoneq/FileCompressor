// Huffman Tree Debugging Helper Functions
// Add these to your Huffman.cpp for better debugging visibility

#include <iomanip>
#include <iostream>

// Helper function to print frequency map
void printFrequencyMap(const std::map<char, unsigned int>& frequency) {
    std::cout << "\n=== CHARACTER FREQUENCIES ===" << std::endl;
    std::cout << std::setw(10) << "Character" << std::setw(15) << "Frequency" << std::endl;
    std::cout << std::string(25, '-') << std::endl;

    for (const auto& pair : frequency) {
        char c = pair.first;
        if (c == '\n') {
            std::cout << std::setw(10) << "\\n" << std::setw(15) << pair.second << std::endl;
        } else if (c == '\t') {
            std::cout << std::setw(10) << "\\t" << std::setw(15) << pair.second << std::endl;
        } else if (c == ' ') {
            std::cout << std::setw(10) << "SPACE" << std::setw(15) << pair.second << std::endl;
        } else {
            std::cout << std::setw(10) << c << std::setw(15) << pair.second << std::endl;
        }
    }
    std::cout << std::string(25, '=') << std::endl;
}

// Helper function to print priority queue state
void printPriorityQueueState(
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> pq_copy) {
    std::cout << "\n=== PRIORITY QUEUE STATE ===" << std::endl;
    std::cout << "Queue size: " << pq_copy.size() << std::endl;

    int count = 0;
    while (!pq_copy.empty() && count < 10) {  // Show first 10 elements
        Node* node = pq_copy.top();
        pq_copy.pop();

        std::cout << "Node " << count + 1 << ": ";
        if (node->leftSon == nullptr && node->rightSon == nullptr) {
            // Leaf node
            char c = node->encodedChar;
            if (c == '\n') {
                std::cout << "Leaf('\\n', freq=" << node->value << ")";
            } else if (c == '\t') {
                std::cout << "Leaf('\\t', freq=" << node->value << ")";
            } else if (c == ' ') {
                std::cout << "Leaf('SPACE', freq=" << node->value << ")";
            } else {
                std::cout << "Leaf('" << c << "', freq=" << node->value << ")";
            }
        } else {
            // Internal node
            std::cout << "Internal(freq=" << node->value << ")";
        }
        std::cout << std::endl;
        count++;
    }

    if (pq_copy.size() > 10) {
        std::cout << "... and " << (pq_copy.size() - 10) << " more nodes" << std::endl;
    }
    std::cout << std::string(29, '=') << std::endl;
}

// Helper function to print tree structure (recursive)
void printTreeStructure(Node* node, int depth = 0, const std::string& prefix = "") {
    if (node == nullptr) return;

    std::cout << prefix;

    if (node->leftSon == nullptr && node->rightSon == nullptr) {
        // Leaf node
        char c = node->encodedChar;
        if (c == '\n') {
            std::cout << "├─ Leaf: '\\n' (freq=" << node->value << ")" << std::endl;
        } else if (c == '\t') {
            std::cout << "├─ Leaf: '\\t' (freq=" << node->value << ")" << std::endl;
        } else if (c == ' ') {
            std::cout << "├─ Leaf: 'SPACE' (freq=" << node->value << ")" << std::endl;
        } else {
            std::cout << "├─ Leaf: '" << c << "' (freq=" << node->value << ")" << std::endl;
        }
    } else {
        // Internal node
        std::cout << "├─ Internal (freq=" << node->value << ")" << std::endl;

        if (node->leftSon) {
            std::cout << prefix << "│  └─ Left:" << std::endl;
            printTreeStructure(node->leftSon, depth + 1, prefix + "│     ");
        }

        if (node->rightSon) {
            std::cout << prefix << "│  └─ Right:" << std::endl;
            printTreeStructure(node->rightSon, depth + 1, prefix + "│     ");
        }
    }
}

// Helper function to validate tree structure
bool validateHuffmanTree(Node* node) {
    if (node == nullptr) return false;

    // If it's a leaf, it should have a character and no children
    if (node->leftSon == nullptr && node->rightSon == nullptr) {
        return node->encodedChar != '\0';  // Should have a valid character
    }

    // If it's internal, it should have both children and no character
    if (node->leftSon != nullptr && node->rightSon != nullptr) {
        unsigned int expectedValue = node->leftSon->value + node->rightSon->value;
        bool valueCorrect = (node->value == expectedValue);
        bool childrenValid =
            validateHuffmanTree(node->leftSon) && validateHuffmanTree(node->rightSon);

        if (!valueCorrect) {
            std::cout << "ERROR: Internal node has incorrect value. Expected: " << expectedValue
                      << ", Got: " << node->value << std::endl;
        }

        return valueCorrect && childrenValid;
    }

    // Node has only one child - this is invalid
    std::cout << "ERROR: Node has only one child (should have 0 or 2)" << std::endl;
    return false;
}

/*
HOW TO USE THESE DEBUGGING FUNCTIONS:

1. Add these functions to your Huffman.cpp file
2. In createHuffmanTree(), add debugging calls:

void HuffmanTree::createHuffmanTree(const string& fileName) {
    // ... your existing code for frequency counting ...

    // Debug: Print frequency map
    printFrequencyMap(frequency);

    // ... your existing code for adding nodes to priority queue ...

    // Debug: Print initial priority queue state
    printPriorityQueueState(pq);

    // ... your tree building loop ...

    // Debug: Print final tree structure
    std::cout << "\n=== FINAL HUFFMAN TREE ===" << std::endl;
    printTreeStructure(root);

    // Debug: Validate tree structure
    bool isValid = validateHuffmanTree(root);
    std::cout << "\nTree validation: " << (isValid ? "PASSED" : "FAILED") << std::endl;
}

3. Set breakpoints at these debug function calls to see detailed information
4. Use the debug console to call these functions manually during debugging
*/
