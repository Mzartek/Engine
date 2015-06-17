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

	get_resolution();

	// We call the instance for init
	Graphics::GraphicsRenderer::Instance().initGLWindow("Demo OpenGL", width, height, false);
	Audio::AudioRenderer::Instance();

	std::shared_ptr<Graphics::ShaderProgram> _windowProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/window/windowVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/window/windowFrag.glsl"));
	Graphics::GraphicsRenderer::Instance().setShaderProgram(_windowProgram);

	std::shared_ptr<Demo> demo(new Demo);
	demo->launch();

	return 0;
}
