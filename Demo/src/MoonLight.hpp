#ifndef MOONLIGHT_HEADER
#define MOONLIGHT_HEADER

#include <Engine/Graphics/DirLight.hpp>

class MoonLight
{
private:
	std::shared_ptr<Engine::ShaderProgram> _dirLightProgram;
	std::shared_ptr<Engine::DirLight> _light;
public:
	MoonLight(void);
	~MoonLight(void);
	const std::shared_ptr<Engine::DirLight> &getLight(void) const;
};

#endif