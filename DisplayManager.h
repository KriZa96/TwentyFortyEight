#pragma once

#include <iostream>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <GL/gl.h>
#pragma comment(lib, "opengl32.lib")
#endif

class DisplayManager {
 private:
  GLFWwindow* window;
  int width;
  int height;

 public:
  DisplayManager() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    createWindow();
  }

  ~DisplayManager() {
    if (window) {
      glfwDestroyWindow(window);
    }
    glfwTerminate();
  }

  void createWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(monitor, nullptr, nullptr, &width, &height);

    window = glfwCreateWindow(width, height, "2048 Game", monitor, nullptr);
    glfwGetFramebufferSize(window, &width, &height);

    if (!window) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
  }

  GLFWwindow* getWindow() const { return window; }

  int getWidth() const { return width; }

  int getHeight() const { return height; }

  void clearScreen() {
    glViewport(0, 0, width, height);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void swapBuffers() { glfwSwapBuffers(window); }

  bool shouldClose() const { return glfwWindowShouldClose(window); }

};