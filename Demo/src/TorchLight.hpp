#ifndef TORCHLIGHT_HEADER
#define TORCHLIGHT_HEADER

#include <Engine/Graphics/SpotLight.hpp>

class TorchLight
{
private:
	std::shared_ptr<Engine::ShaderProgram> _spotLightProgram;
	std::shared_ptr<Engine::SpotLight> _light;
public:
	TorchLight(void);
	~TorchLight(void);
	const std::shared_ptr<Engine::SpotLight> &getLight(void) const;
};

#endif