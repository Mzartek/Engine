#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl");

	_light = new Engine::SpotLight(_spotLightProgram);
}

TorchLight::~TorchLight(void)
{
	delete _spotLightProgram;
	delete _light;
}

Engine::SpotLight *TorchLight::getLight(void) const
{
	return _light;
}