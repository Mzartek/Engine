#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl"));

	_light = std::shared_ptr<Graphics::SpotLight>(new Graphics::SpotLight(_spotLightProgram));
}

TorchLight::~TorchLight(void)
{
}

const std::shared_ptr<Graphics::SpotLight> &TorchLight::getLight(void) const
{
	return _light;
}