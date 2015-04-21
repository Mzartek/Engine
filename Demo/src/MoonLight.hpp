#ifndef MOONLIGHT_HEADER
#define MOONLIGHT_HEADER

#include <Engine/Engine.hpp>

class MoonLight
{
private:
	Engine::ShaderProgram *_dirLightProgram;
	Engine::DirLight *_light;
public:
	MoonLight(void);
	~MoonLight(void);
	Engine::DirLight *getLight(void) const;
};

#endif