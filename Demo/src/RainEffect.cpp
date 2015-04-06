#include "RainEffect.hpp"

RainEffect::RainEffect(void)
{
	_direction = new glm::vec3(0.0f, -1.0f, 1.0f);

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
}

RainEffect::~RainEffect(void)
{
	delete _direction;
	delete _physicsRainProgram;
	delete _displayRainProgram;
	delete _rainManager;
}

void RainEffect::init(const glm::vec3 &position, const unsigned int &numParticles)
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

void RainEffect::setDirection(const glm::vec3 &direction)
{
	*_direction = direction;
}

void RainEffect::updateParticles(const glm::vec3 &position)
{
	_rainManager->setPosition(position);
	_rainManager->updateParticles();
}

void RainEffect::display(Engine::GBuffer *gbuf, Engine::Camera *cam)
{
	_rainManager->display(gbuf, cam);
}