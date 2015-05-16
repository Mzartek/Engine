#ifndef THUNDERLIGHT_HEADER
#define THUNDERLIGHT_HEADER

#include <Engine/Graphics/DirLight.hpp>
#include <Engine/Audio/Sound.hpp>

class ThunderLight
{
private:
	std::shared_ptr<Engine::ShaderProgram> _dirLightProgram;
	std::shared_ptr<Engine::DirLight> _light;
	std::shared_ptr<Engine::Sound> _sound[4];

public:
	ThunderLight(void);
	~ThunderLight(void);
	void generateDirection(void);
	void playRandomSound(void);
	const std::shared_ptr<Engine::DirLight> &getLight(void) const;
};

#endif