#pragma once

#include "../Renderer.h"
#include "../DisplayManager.h"
#include "../InputManager.h"
#include "../TwentyFortyEight.h"


class Application {
 private:
  std::unique_ptr<DisplayManager> displayManager;
  std::unique_ptr<InputManager> inputManager;
  std::unique_ptr<TwentyFortyEight> game;
  std::unique_ptr<Renderer> renderer;

 public:
  Application();
  ~Application();

  void run();
  static void start();
};
