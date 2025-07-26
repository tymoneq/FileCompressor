# File Compressor Debugger Setup

This debugging configuration allows you to debug your C++ file compressor and decompressor programs in VS Code.

## Debug Configurations Available

1. **Debug Compressor** - Debug the compression program with `test.txt` as input
2. **Debug Decompressor** - Debug the decompression program 
3. **C/C++ Runner: Debug Session** - Generic debug session

## How to Use the Debugger

### Setting Breakpoints
1. Open either `compressor.cpp` or `decompress.cpp`
2. Click in the left margin next to line numbers to set breakpoints
3. Red dots will appear indicating breakpoints

### Starting Debug Session
1. Go to **Run and Debug** view (Ctrl+Shift+D)
2. Select your desired configuration from the dropdown
3. Press F5 or click the green play button

### Debug Controls
- **F5** - Continue execution
- **F10** - Step over (next line)
- **F11** - Step into (enter function)
- **Shift+F11** - Step out (exit function)
- **Ctrl+Shift+F5** - Restart debugging
- **Shift+F5** - Stop debugging

### Useful Debug Features
- **Variables panel** - Shows variable values in current scope
- **Watch panel** - Add expressions to monitor
- **Call Stack** - Shows function call hierarchy
- **Debug Console** - Execute expressions during debugging

## Tasks Available

You can run these tasks from the Command Palette (Ctrl+Shift+P):

1. **build-debug** - Build project in debug mode
2. **build-release** - Build project in release mode  
3. **run-compressor** - Run compressor with test.txt
4. **run-decompressor** - Run decompressor
5. **run-full-pipeline** - Run both compressor and decompressor in sequence
6. **clean** - Clean build directory

## Debugging Tips

### For Compressor (`compressor.cpp`):
- Set breakpoints at:
  - Line where file is read (`file >> row`)
  - Dictionary building logic
  - Frequency counting
  - Output writing

### For Decompressor (`decompress.cpp`):
- Set breakpoints at:
  - Dictionary reading from `legend.txt`
  - Compression file reading
  - Decompression logic (around line 55-65)
  - Output writing

### Common Debug Scenarios:
1. **Check dictionary contents** - Add dictionary variables to Watch panel
2. **Verify file reading** - Step through file input loops
3. **Trace compression logic** - Step through encoding/decoding algorithms
4. **Monitor variable states** - Use Variables panel to see current values

## File Structure for Debugging

Make sure these files exist for proper testing:
- `test.txt` - Input file for compression
- `compress.txt` - Output from compressor (input to decompressor)  
- `legend.txt` - Dictionary file created by compressor
- `decompress.txt` - Final decompressed output

## Fixing the Current Issue

I noticed in your `decompress.cpp` on line 72, there's just "close" which should be:
```cpp
compress.close();
decompress.close();
```

The build warnings also suggest:
1. Use `size_t` instead of `int` for loop variables when comparing with `.size()`
2. Remove unused parameters or use `(void)argc; (void)argv;` to suppress warnings
