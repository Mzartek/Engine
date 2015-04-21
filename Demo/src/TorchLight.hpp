#ifndef TORCHLIGHT_HEADER
#define TORCHLIGHT_HEADER

#include <Engine/Engine.hpp>

class TorchLight
{
private:
	Engine::ShaderProgram *_spotLightProgram;
	Engine::SpotLight *_light;
public:
	TorchLight(void);
	~TorchLight(void);
	Engine::SpotLight *getLight(void) const;
};

#endif