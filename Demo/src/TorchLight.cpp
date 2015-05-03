#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl"));

	_light = new_ptr(Engine::SpotLight(_spotLightProgram));
}

TorchLight::~TorchLight(void)
{
	release_ptr(_spotLightProgram);
	release_ptr(_light);
}

Engine::SpotLight *TorchLight::getLight(void) const
{
	return _light;
}