#pragma once
#include "glad/glad.h"
// #include "GLFW/include/glfw3.h"

namespace BorderlessEngine
{
	class InputSystem
	{
	public:
		static bool Initialize(GLFWwindow *window);
		static void Update(GLFWwindow *window);
		static void FixedUpdate();
		static void Destroy();

	private:
		static void processInput(GLFWwindow *window);
		static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
	};

}