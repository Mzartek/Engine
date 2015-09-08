#include "MoonLight.hpp"

MoonLight::MoonLight(void)
{
	_dirLightProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/dirLight/dirLightVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/dirLight/dirLightFrag.glsl");

	_light = std::make_shared<Graphics::DirLight>(_dirLightProgram);

	_light->setColor(glm::vec3(0.5f, 0.5f, 0.9f));
	_light->setDirection(glm::vec3(0.5f, -1.0f, 0.0f));
}

MoonLight::~MoonLight(void)
{
}

const std::shared_ptr<Graphics::DirLight> &MoonLight::getLight(void) const
{
	return _light;
}