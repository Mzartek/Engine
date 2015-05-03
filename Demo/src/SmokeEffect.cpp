#include "SmokeEffect.hpp"

SmokeEffect::SmokeEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsSmokeProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/smokeParticles/smokePhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/smokeParticles/smokePhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *)));

	_displaySmokeProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/smokeParticles/smokeVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/smokeParticles/smokeGeom.glsl",
		"../share/Demo/shader/smokeParticles/smokeFrag.glsl"));

	_smokeManager = new_ptr(Engine::ParticlesManager(_physicsSmokeProgram, _displaySmokeProgram));

	_fire_sound = new_ptr(Engine::Sound);
}

SmokeEffect::~SmokeEffect(void)
{
	release_ptr(_physicsSmokeProgram);
	release_ptr(_displaySmokeProgram);
	release_ptr(_smokeManager);
	release_ptr(_fire_sound);
}

void SmokeEffect::init(const glm::vec3 &position, const unsigned int &numParticles) const
{
	std::vector<Engine::Particle> smokeParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		smokeParticles[i].position = position;
		smokeParticles[i].direction = glm::vec3((GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 1.0f, (GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX);
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	_smokeManager->loadTexture("../share/Demo/resources/textures/smoke.png");
	_smokeManager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
}

void SmokeEffect::setPosition(const glm::vec3 &pos)
{
	_smokeManager->setPosition(pos);
	_fire_sound->setPosition(pos);
}

Engine::ParticlesManager *SmokeEffect::getParticlesManager(void) const
{
	return _smokeManager;
}

Engine::Sound *SmokeEffect::getSound(void) const
{
	return _fire_sound;
}