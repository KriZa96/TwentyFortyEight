#pragma once

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Application.h"


Application::Application()
    : displayManager(std::make_unique<DisplayManager>()),
    inputManager(std::make_unique<InputManager>(displayManager->getWindow())),
    game(std::make_shared<TwentyFortyEightEngine>()),
      renderer(std::make_unique<Renderer>(game, displayManager->getWidth(),
                                          displayManager->getHeight())) {

    inputManager->setGame(game.get());
    inputManager->setupKeyCallback();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(displayManager->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run() {
    while (!displayManager->shouldClose()) {
        inputManager->pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer->renderGame();
        ImGui::Render();

        displayManager->clearScreen();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        displayManager->swapBuffers();
    }
}

void Application::start() {
    Application app;
    app.run();
}
