#include "ExplosionEffect.hpp"

ExplosionEffect::ExplosionEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/explosionParticles/explosionPhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/explosionParticles/explosionPhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/explosionParticles/explosionVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/explosionParticles/explosionGeom.glsl",
		"../share/Demo/shader/explosionParticles/explosionFrag.glsl"));

	_manager = std::shared_ptr<Graphics::ParticlesManager>(new Graphics::ParticlesManager(_physicsProgram, _displayProgram));
	_manager->loadTexture("../share/Demo/resources/textures/fire.png");

	_sound = std::shared_ptr<Audio::Sound>(new Audio::Sound);
	_sound->setGain(1);
	_sound->setPitch(1);
	_sound->setLoop(AL_FALSE);
	_sound->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
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
			(GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX, 
			(GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX,
			(GLfloat)(rand() - (RAND_MAX / 2)) / RAND_MAX);
		smokeParticles[i].velocity = ((GLfloat)rand() / RAND_MAX) * 1.8f;
		smokeParticles[i].life = (GLfloat)(rand() % 100);
	}
	_manager->setParticles(smokeParticles.data(), (GLsizei)smokeParticles.size());
	this->setPosition(position);
}

void ExplosionEffect::setPosition(const glm::vec3 &pos)
{
	_manager->setPosition(pos);
	_sound->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesManager> &ExplosionEffect::getParticlesManager(void) const
{
	return _manager;
}

const std::shared_ptr<Audio::Sound> &ExplosionEffect::getSound(void) const
{
	return _sound;
}

void ExplosionEffect::updateParticles(void) const
{
	_manager->updateParticles();
}
