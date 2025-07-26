// Debugging Helper Functions for FileCompressor
// Add these functions to your code for better debugging visibility

#include <iostream>
#include <map>
#include <string>

// Helper function to print dictionary contents (for compressor.cpp)
void printDictionary(const std::map<std::string, std::pair<int, int>>& dict) {
    std::cout << "\n=== DICTIONARY CONTENTS ===" << std::endl;
    for (const auto& pair : dict) {
        std::cout << "Word: '" << pair.first << "' -> Frequency: " << pair.second.first
                  << ", Code: " << pair.second.second << std::endl;
    }
    std::cout << "========================\n" << std::endl;
}

// Helper function to print dictionary contents (for decompress.cpp)
void printDecompressDictionary(const std::map<int, std::string>& dict) {
    std::cout << "\n=== DECOMPRESS DICTIONARY ===" << std::endl;
    for (const auto& pair : dict) {
        std::cout << "Code: " << pair.first << " -> Word: '" << pair.second << "'" << std::endl;
    }
    std::cout << "==========================\n" << std::endl;
}

// Helper function to debug file reading
void debugFileRead(const std::string& filename, const std::string& content) {
    std::cout << "Reading from " << filename << ": '" << content << "'" << std::endl;
}

// Helper function to debug compression process
void debugCompression(const std::string& original, const std::string& compressed) {
    std::cout << "Original: '" << original << "' -> Compressed: '" << compressed << "'"
              << std::endl;
}

/*
DEBUGGING TIPS FOR YOUR SPECIFIC CODE:

1. In compressor.cpp, add debugging after line ~30:
   std::cout << "Read word: " << row << std::endl;

2. In compressor.cpp, add debugging after dictionary building:
   printDictionary(dictionary);

3. In decompress.cpp, add debugging after dictionary loading:
   printDecompressDictionary(dictionary);

4. In decompress.cpp, add debugging in the decompression loop:
   std::cout << "Processing: " << row << std::endl;

5. Set breakpoints at these key locations:
   - compressor.cpp line ~30 (file reading loop)
   - compressor.cpp line ~40 (dictionary building)
   - decompress.cpp line ~40 (dictionary reading)
   - decompress.cpp line ~55 (decompression loop)

6. Watch these variables during debugging:
   - dictionary (both programs)
   - row (current word being processed)
   - num (calculated numbers)
   - word (current word being built)

7. Common issues to debug:
   - File not opening (check file.is_open())
   - Dictionary not building correctly
   - Number parsing issues in getNum()
   - File output not working

8. Use the debug console to run expressions like:
   - dictionary.size()
   - row.length()
   - dictionary[key]
*/
