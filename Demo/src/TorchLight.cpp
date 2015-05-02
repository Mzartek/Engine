#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl"));

	_light = new_ref(Engine::SpotLight(_spotLightProgram));
}

TorchLight::~TorchLight(void)
{
	release_ref(_spotLightProgram);
	release_ref(_light);
}

Engine::SpotLight *TorchLight::getLight(void) const
{
	return _light;
}