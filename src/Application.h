#pragma once

#include "Renderer.h"
#include "DisplayManager.h"
#include "TwentyFortyEightEngine.h"


class Application {
private:
	std::unique_ptr<DisplayManager> displayManager;
	std::shared_ptr<TwentyFortyEightEngine> game;
	std::unique_ptr<Renderer> renderer;

public:
	Application();
	~Application();

	void run();
	static void start();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
