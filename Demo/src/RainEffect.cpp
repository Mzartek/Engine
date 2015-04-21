#include "RainEffect.hpp"

RainEffect::RainEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsRainProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/rainParticles/rainPhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/rainParticles/rainPhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *));

	_displayRainProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/rainParticles/rainVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/rainParticles/rainGeom.glsl",
		"../share/Demo/shader/rainParticles/rainFrag.glsl");

	_rainManager = new Engine::ParticlesManager(_physicsRainProgram, _displayRainProgram);

	_rain_sound = new Engine::Sound;
}

RainEffect::~RainEffect(void)
{
	delete _physicsRainProgram;
	delete _displayRainProgram;
	delete _rainManager;
	delete _rain_sound;
}

void RainEffect::init(const glm::vec3 &position, const unsigned int &numParticles) const
{
	std::vector<Engine::Particle> rainParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		rainParticles[i].position = glm::vec3(position.x + (rand() % 200 - 100), position.y + 100, position.z + (rand() % 200 - 100));
		rainParticles[i].direction = glm::vec3(0, -1, 0);
		rainParticles[i].velocity = 2.0f;
		rainParticles[i].life = (GLfloat)(rand() % 100);
	}
	_rainManager->loadTexture("../share/Demo/resources/textures/goutte.png");
	_rainManager->setParticles(rainParticles.data(), (GLsizei)rainParticles.size());
}

Engine::ParticlesManager *RainEffect::getParticlesManager() const
{
	return _rainManager;
}

Engine::Sound *RainEffect::getSound(void) const
{
	return _rain_sound;
}