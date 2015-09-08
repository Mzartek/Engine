#include "SmokeEffect.hpp"

SmokeEffect::SmokeEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/smokeParticles/smokePhysics_v.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/smokeParticles/smokePhysics_g.glsl",
		nullptr,
		varyings, static_cast<GLsizei>(sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/smokeParticles/smokeVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/smokeParticles/smokeGeom.glsl",
		"../share/Demo/shader/smokeParticles/smokeFrag.glsl");

	_particlesHandler = std::make_shared<Graphics::ParticlesHandler>(_physicsProgram, _displayProgram);
	_particlesHandler->loadTexture("../share/Demo/resources/textures/smoke.png");

	_sound = std::make_shared<Audio::Sound>();
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
	std::vector<Graphics::Particle> smokeParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		smokeParticles[i].position = position;
		smokeParticles[i].direction = glm::normalize(glm::vec3(
			static_cast<GLfloat>(rand() - (RAND_MAX / 2)) / RAND_MAX,
			1.0f,
			static_cast<GLfloat>(rand() - (RAND_MAX / 2)) / RAND_MAX));
		smokeParticles[i].velocity = 0.2f;
		smokeParticles[i].life = static_cast<GLfloat>(rand() % 100);
	}
	_particlesHandler->setParticles(smokeParticles.data(), static_cast<GLsizei>(smokeParticles.size()));
	this->setPosition(position);
}

void SmokeEffect::setPosition(const glm::vec3 &pos)
{
	_particlesHandler->setPosition(pos);
	_sound->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesHandler> &SmokeEffect::getParticlesHandler(void) const
{
	return _particlesHandler;
}

const std::shared_ptr<Audio::Sound> &SmokeEffect::getSound(void) const
{
	return _sound;
}

void SmokeEffect::updateParticles(void) const
{
	_particlesHandler->updateParticles();
}