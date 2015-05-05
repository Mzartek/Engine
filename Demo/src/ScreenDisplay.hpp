#ifndef SCREENDISPLAY_HEADER
#define SCREENDISPLAY_HEADER

#include <Engine/Graphics/Screen.hpp>

class ScreenDisplay
{
private:
	std::shared_ptr<Engine::ShaderProgram> _backgroundProgram;
	std::shared_ptr<Engine::ShaderProgram> _screenProgram;
	std::shared_ptr<Engine::Screen> _screen;
public:
	ScreenDisplay(void);
	~ScreenDisplay(void);
	const std::shared_ptr<Engine::Screen> &getScreen(void) const;
};

#endif