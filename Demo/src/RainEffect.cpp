#include "RainEffect.hpp"

RainEffect::RainEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsRainProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/rainParticles/rainPhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/rainParticles/rainPhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *)));

	_displayRainProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/rainParticles/rainVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/rainParticles/rainGeom.glsl",
		"../share/Demo/shader/rainParticles/rainFrag.glsl"));

	_rainManager = std::shared_ptr<Engine::ParticlesManager>(new Engine::ParticlesManager(_physicsRainProgram, _displayRainProgram));

	_rain_sound = std::shared_ptr<Engine::Sound>(new Engine::Sound);
}

RainEffect::~RainEffect(void)
{
}

void RainEffect::init(const glm::vec3 &position, GLuint numParticles) const
{
	std::vector<Engine::Particle> rainParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		rainParticles[i].life = (GLfloat)(rand() % 100);
		rainParticles[i].position = glm::vec3(position.x + (rand() % 200 - 100), position.y + (100 - rainParticles[i].life), position.z + (rand() % 200 - 100));
		rainParticles[i].direction = glm::vec3(0, -1, 0);
		rainParticles[i].velocity = 2.0f;
	}
	_rainManager->loadTexture("../share/Demo/resources/textures/goutte.png");
	_rainManager->setParticles(rainParticles.data(), (GLsizei)rainParticles.size());
}

const std::shared_ptr<Engine::ParticlesManager> &RainEffect::getParticlesManager() const
{
	return _rainManager;
}

const std::shared_ptr<Engine::Sound> &RainEffect::getSound(void) const
{
	return _rain_sound;
}
