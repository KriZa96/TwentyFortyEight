#pragma once

#include <iostream>

#include "Config.h"
#include "DisplayManager.h"

#ifdef _WIN32
#include <GL/gl.h>
#pragma comment(lib, "opengl32.lib")
#endif


DisplayManager::DisplayManager() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                   DisplayConfig::OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                   DisplayConfig::OPENGL_VERSION_MINOR);

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

    window = glfwCreateWindow(width, height, DisplayConfig::WINDOW_TITLE, monitor, nullptr);
    glfwGetFramebufferSize(window, &width, &height);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(DisplayConfig::VSYNC_ENABLED);
}


GLFWwindow* DisplayManager::getWindow() const { return window; }


int DisplayManager::getWidth() const { return width; }


int DisplayManager::getHeight() const { return height; }


void DisplayManager::clearScreen() {
    glViewport(0, 0, width, height);
    glClearColor(
        DisplayConfig::BACKGROUND_COLOR.x,
        DisplayConfig::BACKGROUND_COLOR.y,
        DisplayConfig::BACKGROUND_COLOR.z,
        DisplayConfig::BACKGROUND_COLOR.w
    );
    glClear(GL_COLOR_BUFFER_BIT);
}


void DisplayManager::swapBuffers() { glfwSwapBuffers(window); }


bool DisplayManager::shouldClose() const {
    return glfwWindowShouldClose(window);
}
