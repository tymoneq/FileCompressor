# Huffman Tree Debugging Guide

This guide provides specific debugging strategies for your Huffman tree implementation.

## Debug Configurations Available

1. **Debug Main (Huffman Tree)** - Debug your main application that creates the Huffman tree
2. **Debug Huffman Tree Construction** - Same as above but stops at entry for step-by-step debugging
3. **Debug Compressor** - Debug the old compressor implementation
4. **Debug Decompressor** - Debug the old decompressor implementation

## Key Debugging Points for Huffman Tree

### 1. In main.cpp
- **Line 11**: `HuffmanTree huffmanTree;` - Constructor call
- **Line 13**: `huffmanTree.createHuffmanTree(fileName);` - Tree creation

### 2. In Huffman.cpp - createHuffmanTree function

#### Frequency Counting (Lines 25-30)
```cpp
// Set breakpoint here to debug character frequency counting
while (getline(file, row)) {
    for (const char& c : row) frequency[c]++;  // <- BREAKPOINT HERE
}
```

#### Node Creation (Line 32)
```cpp
// Set breakpoint to see leaf nodes being created
for (const auto& el : frequency) pq.push(createNode(el.first, el.second, nullptr, nullptr));
```

#### Tree Construction Loop (Lines 35-43)
```cpp
// Critical debugging point - tree building logic
while (!pq.size() == 1) {  // <- POTENTIAL BUG HERE!
    auto leftSon = pq.top();   // <- BREAKPOINT HERE
    pq.pop();
    
    auto rightSon = pq.top();
    pq.pop();
    
    auto newNode = createNode('.', leftSon->value + rightSon->value, leftSon, rightSon);
    pq.push(newNode);
}
```

## Critical Bug Found!

**Line 35 in Huffman.cpp has a bug:**
```cpp
while (!pq.size() == 1)  // WRONG!
```

Should be:
```cpp
while (pq.size() > 1)    // CORRECT!
```

The current condition `!pq.size() == 1` is equivalent to `!(pq.size() == 1)` which will cause an infinite loop!

## Variables to Watch During Debugging

### In createHuffmanTree:
1. `frequency` - Map showing character frequencies
2. `pq.size()` - Size of priority queue
3. `leftSon->value` and `rightSon->value` - Node frequencies
4. `root` - Final root node

### In createNode:
1. `character` - Character being stored
2. `value` - Frequency/weight of the node
3. `leftSon` and `rightSon` - Child pointers

## Debugging Expressions for Debug Console

```cpp
// Check frequency map
frequency.size()
frequency['a']  // Replace 'a' with any character

// Check priority queue
pq.size()
pq.empty()

// Check node values
leftSon->value
rightSon->value
leftSon->encodedChar
rightSon->encodedChar

// Check if node is leaf
leftSon->leftSon == nullptr && leftSon->rightSon == nullptr
```

## Step-by-Step Debugging Process

### 1. Start with "Debug Huffman Tree Construction"
- This stops at entry, allowing you to set breakpoints first

### 2. Set Strategic Breakpoints:
- `main.cpp` line 13 (before tree creation)
- `Huffman.cpp` line 28 (frequency counting loop)
- `Huffman.cpp` line 32 (node creation)
- `Huffman.cpp` line 36 (tree construction loop)
- `Huffman.cpp` line 44 (after tree completion)

### 3. Debug the Frequency Map:
- Step through the file reading
- Watch the `frequency` map grow
- Verify correct character counts

### 4. Debug Node Creation:
- Watch nodes being created and added to priority queue
- Verify each node has correct frequency and character

### 5. Debug Tree Construction:
- **IMPORTANT**: Fix the loop condition first!
- Watch the priority queue size decrease
- Verify parent nodes have correct combined frequencies
- Check that final root node is created

## Common Issues to Debug

1. **Infinite Loop**: Fix `while (!pq.size() == 1)` to `while (pq.size() > 1)`
2. **Empty File**: Check if `test.txt` exists and has content
3. **Memory Leaks**: Add destructor implementation to clean up nodes
4. **Priority Queue Order**: Verify NodeComparator is working correctly

## Expected Debugging Flow

1. **Frequency counting** should populate the map with character frequencies
2. **Node creation** should create one leaf node per unique character  
3. **Tree construction** should repeatedly combine two smallest nodes
4. **Final result** should be a single root node containing the entire tree

## Memory Debugging

Since you're using `new Node()`, consider adding debug output in the destructor:

```cpp
HuffmanTree::~HuffmanTree() {
    // Add recursive deletion of nodes here
    // Debug: Add output to see when nodes are deleted
}
```

## Quick Fix for Testing

Update line 35 in `Huffman.cpp`:
```cpp
// Change from:
while (!pq.size() == 1)

// To:
while (pq.size() > 1)
```

This will fix the infinite loop and allow proper tree construction!
