#include "SmokeEffect.hpp"

SmokeEffect::SmokeEffect(void)
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
	_manager->loadTexture("../share/Demo/resources/textures/smoke.png");

	_sound = std::shared_ptr<Engine::Sound>(new Engine::Sound);
	_sound->setGain(0.75f);
	_sound->setPitch(0.75f);
	_sound->setLoop(AL_TRUE);
	_sound->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	_sound->setDistances(1.0f, 100.0f);
	_sound->loadFromFile("../share/Demo/resources/sound/fire_mono.wav", 44100, AL_FORMAT_MONO16);
}

SmokeEffect::~SmokeEffect(void)
{
}

void SmokeEffect::init(const glm::vec3 &position, GLuint numParticles)
{
	std::vector<Engine::Particle> smokeParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		smokeParticles[i].position = position;
		smokeParticles[i].direction = glm::normalize(glm::vec3(
			(GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 
			1.0f, 
			(GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX));
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	_manager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
	this->setPosition(position);
}

void SmokeEffect::setPosition(const glm::vec3 &pos)
{
	_manager->setPosition(pos);
	_sound->setPosition(pos);
}

const std::shared_ptr<Engine::ParticlesManager> &SmokeEffect::getParticlesManager(void) const
{
	return _manager;
}

const std::shared_ptr<Engine::Sound> &SmokeEffect::getSound(void) const
{
	return _sound;
}

void SmokeEffect::updateParticles(void) const
{
	_manager->updateParticles();
}