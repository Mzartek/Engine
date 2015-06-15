#ifndef SCREENDISPLAY_HEADER
#define SCREENDISPLAY_HEADER

#include <Engine/Graphics/GBuffer.hpp>
#include <Engine/Graphics/Window.hpp>

using namespace Engine;

class ScreenDisplay
{
private:
		std::shared_ptr<Graphics::ShaderProgram> _windowProgram;
		std::shared_ptr<Graphics::ShaderProgram> _backgroundProgram;
		std::shared_ptr<Graphics::Window> _window;
		std::shared_ptr<Graphics::GBuffer> _gBuffer;

public:
		ScreenDisplay(const GLchar *title, GLint w, GLint h, GLboolean fullScreen);
		~ScreenDisplay(void);
		const std::shared_ptr<Graphics::Window> &getWindow(void) const;
		const std::shared_ptr<Graphics::GBuffer> &getGBuffer(void) const;
};

#endif