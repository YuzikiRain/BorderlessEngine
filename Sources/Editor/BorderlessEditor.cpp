#include "BorderlessEditor.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

namespace BorderlessEditor
{
	void Launch()
	{
		std::cout << "BorderlessEditor launched" << std::endl;
		InitializeWindow();
		GameLoop();
		Quit();
	}

	bool InitializeWindow()
	{
		return 0;
	}

	void GameLoop()
	{

	}


	void Quit()
	{
	}

}
