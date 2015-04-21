#ifndef SCREENDISPLAY_HEADER
#define SCREENDISPLAY_HEADER

#include <Engine/Engine.hpp>

class ScreenDisplay
{
private:
	Engine::ShaderProgram *_backgroundProgram;
	Engine::ShaderProgram *_screenProgram;
	Engine::Screen *_screen;
public:
	ScreenDisplay(void);
	~ScreenDisplay(void);
	Engine::Screen *getScreen(void) const;
};

#endif