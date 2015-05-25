#ifndef SCREENDISPLAY_HEADER
#define SCREENDISPLAY_HEADER

#include <Engine/Graphics/Screen.hpp>

using namespace Engine;

class ScreenDisplay
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _backgroundProgram;
	std::shared_ptr<Graphics::ShaderProgram> _screenProgram;
	std::shared_ptr<Graphics::Screen> _screen;

public:
	ScreenDisplay(void);
	~ScreenDisplay(void);
	const std::shared_ptr<Graphics::Screen> &getScreen(void) const;
};

#endif