#pragma once

#include <iostream>
#include "DisplayManager.h"

#ifdef _WIN32
#include <GL/gl.h>
#pragma comment(lib, "opengl32.lib")
#endif


DisplayManager::DisplayManager() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    createWindow();
}


DisplayManager::~DisplayManager() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}


void DisplayManager::createWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(monitor, nullptr, nullptr, &width, &height);

    window = glfwCreateWindow(width, height, "2048 Game", monitor, nullptr);
    glfwGetFramebufferSize(window, &width, &height);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}


GLFWwindow* DisplayManager::getWindow() const { return window; }


int DisplayManager::getWidth() const { return width; }


int DisplayManager::getHeight() const { return height; }


void DisplayManager::clearScreen() {
    glViewport(0, 0, width, height);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void DisplayManager::swapBuffers() { glfwSwapBuffers(window); }


bool DisplayManager::shouldClose() const {
    return glfwWindowShouldClose(window);
}
