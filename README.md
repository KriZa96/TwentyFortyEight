# TwentyFortyEight

A C++ implementation of the classic 2048 puzzle game using OpenGL and Dear ImGui for rendering.

## About the Game

2048 is a single-player puzzle game where you slide numbered tiles on a 4×4 grid to combine them. When two tiles with the same number touch, they merge into one tile with the sum of their values. The goal is to create a tile with the number 2048.

This implementation features:
- Clean, minimalist interface
- Score tracking
- Cross-platform compatibility
- Playable after reaching 2048 for achieveing higher scores

## Technologies Used

- **C++20**: Core programming language
- **OpenGL**: Graphics rendering
- **GLFW**: Cross-platform window and input handling
- **GLAD**: OpenGL function loader
- **Dear ImGui**: Immediate-mode GUI framework
- **CMake**: Build system
- **vcpkg**: Package manager for dependencies

## Prerequisites

- Visual Studio 2022 (recommended)
- CMake 3.8 or higher (installed with Visual Studio)
- vcpkg package manager (installed with Visual Studio)

## Installation and Setup

### Using Visual Studio 2022

1. **Clone the repository**
   ```
   git clone https://github.com/yourusername/TwentyFortyEight.git
   # or use Visual Studios clone project feature
   ```

2. **Open in Visual Studio 2022**
   - Open Visual Studio and select "Open a local folder"
   - Navigate to the project directory
   - Visual Studio should detect the CMake configuration automatically

3. **Choose a configuration**
   - Select x64-debug or x64-release from the configuration dropdown

4. **Build and Run**
   - Build the solution (F7)
   - Run the application (F5)

## Game Controls

- **Arrow Keys**: Move tiles (Left, Right, Up, Down)
- **New Game button**: Restart the game
- **Exit button**: Close the application

## Project Structure

- `src/main.cpp`: Entry point
- `src/Application.cpp/h`: Main application management
- `src/TwentyFortyEightEngine.cpp/h`: Game logic and mechanics
- `src/DisplayManager.cpp/h`: Window and OpenGL context setup
- `src/TileRenderer.cpp/h`: Rendering of game tiles with colors
- `src/Renderer.cpp/h`: Overall game UI rendering

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Original 2048 game created by Gabriele Cirulli