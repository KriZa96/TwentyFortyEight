#pragma once

#include <memory>
#include "imgui.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "TwentyFortyEight.h"


class Application {
 private:
  std::unique_ptr<DisplayManager> displayManager;
  std::unique_ptr<InputManager> inputManager;
  std::unique_ptr<TwentyFortyEight> game;
  std::unique_ptr<Renderer> renderer;

 public:
  Application() : 
      displayManager(std::make_unique<DisplayManager>()),
      inputManager(std::make_unique<InputManager>(displayManager->getWindow())),
      game(std::make_unique<TwentyFortyEight>()),
      renderer(std::make_unique<Renderer>()) 
  {
    inputManager->setGame(game.get());
    inputManager->setupKeyCallback();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(displayManager->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
  }

  ~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void run() {
    while (!displayManager->shouldClose()) {
      inputManager->pollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      renderer->renderGame(
          *game,
          [this]() { game->reset(); },
          displayManager->getWidth(),
          displayManager->getHeight()
      );

      ImGui::Render();
      displayManager->clearScreen();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      displayManager->swapBuffers();
    }
  }
};
