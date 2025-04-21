#pragma once

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "src/TwentyFortyEightEngine.h"

class InputManager {
 private:
  GLFWwindow* window;
  TwentyFortyEightEngine* game;

 public:
  InputManager(GLFWwindow* win) : window(win), game(nullptr) {}

  void setGame(TwentyFortyEightEngine* g) {
    game = g;
    glfwSetWindowUserPointer(window, game);
  }

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    TwentyFortyEightEngine* game =
        static_cast<TwentyFortyEightEngine*>(glfwGetWindowUserPointer(window));
    if (!game) return;

    if (action == GLFW_PRESS) {
      if (!game->isGameOver()) {
        switch (key) {
          case GLFW_KEY_LEFT:
            game->processMove(TwentyFortyEightEngine::LEFT);
            break;
          case GLFW_KEY_RIGHT:
            game->processMove(TwentyFortyEightEngine::RIGHT);
            break;
          case GLFW_KEY_UP:
            game->processMove(TwentyFortyEightEngine::UP);
            break;
          case GLFW_KEY_DOWN:
            game->processMove(TwentyFortyEightEngine::DOWN);
            break;
        }
      }
    }
  }
  
  void setupKeyCallback() { glfwSetKeyCallback(window, keyCallback); }

  void pollEvents() { glfwPollEvents(); }
};