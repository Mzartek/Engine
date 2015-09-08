#include "ExplosionEffect.hpp"

ExplosionEffect::ExplosionEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/explosionParticles/explosionPhysics_v.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/explosionParticles/explosionPhysics_g.glsl",
		nullptr,
		varyings, static_cast<GLsizei>(sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/explosionParticles/explosionVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/explosionParticles/explosionGeom.glsl",
		"../share/Demo/shader/explosionParticles/explosionFrag.glsl");

	_particlesHandler = std::make_shared<Graphics::ParticlesHandler>(_physicsProgram, _displayProgram);
	_particlesHandler->loadTexture("../share/Demo/resources/textures/fire.png");

	_sound = std::make_shared<Audio::Sound>();
	_sound->setGain(1);
	_sound->setPitch(1);
	_sound->setLoop(AL_FALSE);
	_sound->setVelocity(glm::vec3(0, 0, 0));
	_sound->setDistances(1.0f, 500.0f);
	_sound->loadFromFile("../share/Demo/resources/sound/explosion_mono.wav", 44100, AL_FORMAT_MONO16);
}

ExplosionEffect::~ExplosionEffect(void)
{
}

void ExplosionEffect::init(const glm::vec3 &position, GLuint numParticles)
{
	std::vector<Graphics::Particle> smokeParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		smokeParticles[i].position = position;
		smokeParticles[i].direction = glm::vec3(
			static_cast<GLfloat>(rand() - RAND_MAX / 2) / RAND_MAX,
			static_cast<GLfloat>(rand() - RAND_MAX / 2) / RAND_MAX,
			static_cast<GLfloat>(rand() - RAND_MAX / 2) / RAND_MAX);
		smokeParticles[i].velocity = static_cast<GLfloat>(rand()) / RAND_MAX * 1.8f;
		smokeParticles[i].life = static_cast<GLfloat>(rand() % 100);
	}
	_particlesHandler->setParticles(smokeParticles.data(), static_cast<GLsizei>(smokeParticles.size()));
	this->setPosition(position);
}

void ExplosionEffect::setPosition(const glm::vec3 &pos)
{
	_particlesHandler->setPosition(pos);
	_sound->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesHandler> &ExplosionEffect::getParticlesHandler(void) const
{
	return _particlesHandler;
}

const std::shared_ptr<Audio::Sound> &ExplosionEffect::getSound(void) const
{
	return _sound;
}

void ExplosionEffect::updateParticles(void) const
{
	_particlesHandler->updateParticles();
}
