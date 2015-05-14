#include "ExplosionEffect.hpp"

ExplosionEffect::ExplosionEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/smokeParticles/smokePhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/smokeParticles/smokePhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/smokeParticles/smokeVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/smokeParticles/smokeGeom.glsl",
		"../share/Demo/shader/smokeParticles/smokeFrag.glsl"));

	_manager = std::shared_ptr<Engine::ParticlesManager>(new Engine::ParticlesManager(_physicsProgram, _displayProgram));

	_sound = std::shared_ptr<Engine::Sound>(new Engine::Sound);
}

ExplosionEffect::~ExplosionEffect(void)
{
}

void ExplosionEffect::init(const glm::vec3 &position, GLuint numParticles)
{
	std::vector<Engine::Particle> smokeParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		smokeParticles[i].position = position;
		smokeParticles[i].direction = glm::vec3((GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 1.0f, (GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX);
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	_manager->loadTexture("../share/Demo/resources/textures/smoke.png");
	_manager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
	this->setPosition(position);
}

void ExplosionEffect::setPosition(const glm::vec3 &pos)
{
	_manager->setPosition(pos);
	_sound->setPosition(pos);
}

const std::shared_ptr<Engine::ParticlesManager> &ExplosionEffect::getParticlesManager(void) const
{
	return _manager;
}

const std::shared_ptr<Engine::Sound> &ExplosionEffect::getSound(void) const
{
	return _sound;
}

void ExplosionEffect::updateParticles(void) const
{
	_manager->updateParticles();
}