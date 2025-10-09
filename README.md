## VS Code C++ Unity Build Template

This repository provides a starter template for building and running C++ applications in Visual Studio Code, with a focus on Unity builds (single translation unit compilation).

### Features
- Batch build script (`src/build.bat`) for compiling your project using MSVC
- Unity build setup: compiles all code as a single translation unit for faster builds and easier debugging
- Easily customizable for your own project structure
- Debugger integration with VS Code

### Getting Started
1. **Clone this repository** and open it in VS Code.
2. **Add your C++ source files** to the `src/` directory. By default, the build script compiles `main.cpp`.
3. **Build your project** by running the build task (`Build with build.bat`) from the VS Code command palette or terminal.
4. **Configure debugging**:
	- Edit `.vscode/launch.json` to set the correct path to your executable and configure the debugger (MSVC, gdb, etc.).
	- Make sure the executable name matches the output from the build script.

### Customization
- To change the source file(s) being compiled, edit the path in `src/build.bat`.
- You can adjust compiler flags in `build.bat` to set optimization, warnings, or C++ standard version.
- For multi-file unity builds, include all your implementation files in `main.cpp` using `#include`.

### Requirements
- Visual Studio Code
- MSVC (Microsoft Visual C++ compiler) installed and available in your PATH
- Windows OS (batch script is Windows-specific)

### Notes
- This template is designed for single translation unit (unity) builds, which can speed up compilation and simplify linking.
- For more advanced setups, you may want to add tasks for cleaning, testing, or multi-platform support.


