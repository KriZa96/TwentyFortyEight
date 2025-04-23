#pragma once

#include "Renderer.h"
#include "DisplayManager.h"
#include "TwentyFortyEightEngine.h"


class Application {
private:
	DisplayManager displayManager;
	TwentyFortyEightEngine game;
	Renderer renderer;

public:
	Application();
	~Application();

	void run();
	static void start();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
