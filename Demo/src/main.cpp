#include "Demo.hpp"
#include <ctime>

int main(int argc, char **argv)
{
		UNREFERENCED_PARAMETER(argc);
		UNREFERENCED_PARAMETER(argv);

		srand((unsigned int)time(NULL));

		// We call the instance for init
		Graphics::GraphicsRenderer::Instance();
		Audio::AudioRenderer::Instance();
		Input::InputManager::Instance();

		std::shared_ptr<Graphics::Window> window(new Graphics::Window("Demo OpenGL", 800, 600, GL_FALSE));
		std::shared_ptr<Demo> demo(new Demo(window));

		window->mainLoop(demo);

		return 0;
}
