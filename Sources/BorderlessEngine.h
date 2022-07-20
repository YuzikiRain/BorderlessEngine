#pragma once
#include "glad/glad.h"
#include "GLFW/include/glfw3.h"
#include <list>

namespace BorderlessEngine {
    void Launch();
	bool InitializeWindow();
	void InitSystems();
	void GameLoop();
	void Quit();
	bool ShouldQuit();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	double GetFrameInterval();
	double GetFrameRate();

	extern double targetFrameRate;
	extern double realTime;
	extern double frameTime;
	extern double accumulator;
	extern double timeScale;

}