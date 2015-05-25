#ifndef THUNDERLIGHT_HEADER
#define THUNDERLIGHT_HEADER

#include <Engine/Audio/Sound.hpp>
#include <Engine/Graphics/DirLight.hpp>

using namespace Engine;

class ThunderLight
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _dirLightProgram;
	std::shared_ptr<Graphics::DirLight> _light;
	std::shared_ptr<Audio::Sound> _sound[4];

public:
	ThunderLight(void);
	~ThunderLight(void);
	void generateDirection(void);
	void playRandomSound(void);
	const std::shared_ptr<Graphics::DirLight> &getLight(void) const;
};

#endif