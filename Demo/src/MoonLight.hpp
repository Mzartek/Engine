#ifndef MOONLIGHT_HEADER
#define MOONLIGHT_HEADER

#include <Engine/Graphics/Light/DirLight.hpp>

using namespace Engine;

class MoonLight
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _dirLightProgram;
	std::shared_ptr<Graphics::DirLight> _light;

public:
	MoonLight(void);
	~MoonLight(void);
	const std::shared_ptr<Graphics::DirLight> &getLight(void) const;
};

#endif