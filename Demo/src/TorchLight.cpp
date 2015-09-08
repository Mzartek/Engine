#include "TorchLight.hpp"

TorchLight::TorchLight(void)
{
	_spotLightProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/spotLight/spotLightVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/spotLight/spotLightFrag.glsl");

	_light = std::make_shared<Graphics::SpotLight>(_spotLightProgram);
}

TorchLight::~TorchLight(void)
{
}

const std::shared_ptr<Graphics::SpotLight> &TorchLight::getLight(void) const
{
	return _light;
}