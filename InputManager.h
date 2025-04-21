#pragma once

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "TwentyFortyEight.h"

class InputManager {
 private:
  GLFWwindow* window;
  TwentyFortyEight* game;

 public:
  InputManager(GLFWwindow* win) : window(win), game(nullptr) {}

  void setGame(TwentyFortyEight* g) {
    game = g;
    glfwSetWindowUserPointer(window, game);
  }

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    TwentyFortyEight* game = static_cast<TwentyFortyEight*>(glfwGetWindowUserPointer(window));
    if (!game) return;

    if (action == GLFW_PRESS) {
      if (!game->isGameOver()) {
        switch (key) {
          case GLFW_KEY_LEFT:
            game->processMove(TwentyFortyEight::LEFT);
            break;
          case GLFW_KEY_RIGHT:
            game->processMove(TwentyFortyEight::RIGHT);
            break;
          case GLFW_KEY_UP:
            game->processMove(TwentyFortyEight::UP);
            break;
          case GLFW_KEY_DOWN:
            game->processMove(TwentyFortyEight::DOWN);
            break;
        }
      }
    }
  }
  
  void setupKeyCallback() { glfwSetKeyCallback(window, keyCallback); }

  void pollEvents() { glfwPollEvents(); }
};