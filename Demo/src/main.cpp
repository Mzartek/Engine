#include "Demo.hpp"

#if defined(_WIN32) && defined(_DEBUG)
#	define _CRTDBG_MAP_ALLOC
#	include <stdlib.h>
#	include <crtdbg.h>
#endif

void startProgram(void)
{
	// We call the instance for init
	Graphics::GraphicsRenderer::Instance().init("Demo OpenGL", 800, 600, false);
	Audio::AudioRenderer::Instance();

	std::shared_ptr<Demo> demo = std::make_shared<Demo>();
	demo->launch();
}

int main(int argc, char **argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	startProgram();

#if defined(_WIN32) && defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
