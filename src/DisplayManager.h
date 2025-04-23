#pragma once


#include <GLFW/glfw3.h>


class DisplayManager {
public:
    DisplayManager();
    ~DisplayManager();

    void createWindow();
    GLFWwindow* getWindow() const;
    int getWidth() const;
    int getHeight() const;
    void clearScreen();
    void swapBuffers();
    bool shouldClose() const;

private:
    GLFWwindow* window;
    int width;
    int height;
};