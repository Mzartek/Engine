#include "Demo.hpp"

#include <iostream>
#include <fstream>
#include <ctime>

GLuint width, height;

void get_resolution(void)
{
     std::ifstream resolution_file("../share/Demo/config/resolution.txt", std::ifstream::in);

     resolution_file >> width;
     resolution_file >> height;
}

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand((unsigned int)time(NULL));

	// We call the instance for init
	Graphics::GraphicsRenderer::Instance();
	Audio::AudioRenderer::Instance();
	Input::InputManager::Instance();

	get_resolution();

	std::shared_ptr<Graphics::Window> window(new Graphics::Window("Demo OpenGL", width, height, GL_TRUE));
	std::shared_ptr<Demo> demo(new Demo(window));

	window->mainLoop(demo);

	return 0;
}
