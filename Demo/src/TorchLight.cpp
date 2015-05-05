#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl"));

	_light = std::shared_ptr<Engine::SpotLight>(new Engine::SpotLight(_spotLightProgram));
}

TorchLight::~TorchLight(void)
{
}

const std::shared_ptr<Engine::SpotLight> &TorchLight::getLight(void) const
{
	return _light;
}