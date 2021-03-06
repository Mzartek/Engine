#include "MoonLight.hpp"

MoonLight::MoonLight(void)
{
	_dirLightProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/dirLight/dirLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/dirLight/dirLightFrag.glsl"));

	_light = std::shared_ptr<Graphics::DirLight>(new Graphics::DirLight(_dirLightProgram));

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