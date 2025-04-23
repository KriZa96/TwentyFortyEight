#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Application.h"


Application::Application() :
    renderer(game, displayManager.getWidth(), displayManager.getHeight()) 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(displayManager.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glfwSetWindowUserPointer(displayManager.getWindow(), &game);
    glfwSetKeyCallback(displayManager.getWindow(), keyCallback);
}


Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Application::run() {
    while (!displayManager.shouldClose()) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.renderGame();
        ImGui::Render();

        displayManager.clearScreen();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        displayManager.swapBuffers();
    }
}


void Application::start() {
    Application app;
    app.run();
}


void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    TwentyFortyEightEngine* game = static_cast<TwentyFortyEightEngine*>(glfwGetWindowUserPointer(window));
    if (action != GLFW_PRESS || !game || game->isGameOver()) return;

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
