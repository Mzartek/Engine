#include "Demo.hpp"

#include <ctime>

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	srand(static_cast<unsigned int>(time(nullptr)));

	// We call the instance for init
	Graphics::GraphicsRenderer::Instance().init("Demo OpenGL", 800, 600, false);
	Audio::AudioRenderer::Instance();
	
	std::shared_ptr<Demo> demo = std::make_shared<Demo>();
	demo->launch();

	return 0;
}
