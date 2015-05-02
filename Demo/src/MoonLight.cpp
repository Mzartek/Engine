#include "MoonLight.hpp"

MoonLight::MoonLight(void)
{
	_dirLightProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/dirLight/dirLightVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/dirLight/dirLightFrag.glsl"));

	_light = new_ref(Engine::DirLight(_dirLightProgram));

	_light->setColor(glm::vec3(0.5f, 0.5f, 0.9f));
	_light->setDirection(glm::vec3(0.5f, -1.0f, 0.0f));
}

MoonLight::~MoonLight(void)
{
	release_ref(_dirLightProgram);
	release_ref(_light);
}

Engine::DirLight *MoonLight::getLight(void) const
{
	return _light;
}