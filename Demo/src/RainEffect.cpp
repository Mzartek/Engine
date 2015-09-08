#include "RainEffect.hpp"

RainEffect::RainEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/rainParticles/rainPhysics_v.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/rainParticles/rainPhysics_g.glsl",
		nullptr,
		varyings, static_cast<GLsizei>(sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/rainParticles/rainVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/rainParticles/rainGeom.glsl",
		"../share/Demo/shader/rainParticles/rainFrag.glsl");

	_particlesHandler = std::make_shared<Graphics::ParticlesHandler>(_physicsProgram, _displayProgram);
	_particlesHandler->loadTexture("../share/Demo/resources/textures/goutte.png");

	_sound = std::make_shared<Audio::Sound>();
	_sound->setGain(0.25f);
	_sound->setPitch(1.0f);
	_sound->setLoop(AL_TRUE);
	_sound->loadFromFile("../share/Demo/resources/sound/rain_stereo.wav", 44100, AL_FORMAT_STEREO16);
}

RainEffect::~RainEffect(void)
{
}

void RainEffect::init(const glm::vec3 &position, GLuint numParticles)
{
	std::vector<Graphics::Particle> rainParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		rainParticles[i].life = static_cast<GLfloat>(rand() % 100);
		rainParticles[i].position = glm::vec3(position.x + (rand() % 200 - 100), position.y + (100 - rainParticles[i].life), position.z + (rand() % 200 - 100));
		rainParticles[i].direction = glm::vec3(static_cast<GLfloat>(rand() - RAND_MAX / 2) / RAND_MAX,
			-2.0f,
			static_cast<GLfloat>(rand() - (RAND_MAX / 2)) / RAND_MAX);
		rainParticles[i].velocity = 2.0f;
	}
	_particlesHandler->setParticles(rainParticles.data(), static_cast<GLsizei>(rainParticles.size()));
	this->setPosition(position);
}

void RainEffect::setPosition(const glm::vec3 &pos)
{
	_particlesHandler->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesHandler> &RainEffect::getParticlesHandler() const
{
	return _particlesHandler;
}

const std::shared_ptr<Audio::Sound> &RainEffect::getSound(void) const
{
	return _sound;
}

void RainEffect::updateParticles(void) const
{
	_particlesHandler->updateParticles();
}
