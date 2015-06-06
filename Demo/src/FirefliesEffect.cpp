#include "FirefliesEffect.hpp"

FirefliesEffect::FirefliesEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/firefliesParticles/firefliesPhysics_v.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/firefliesParticles/firefliesPhysics_g.glsl",
		NULL,
		varyings, sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/firefliesParticles/firefliesVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/firefliesParticles/firefliesGeom.glsl",
		"../share/Demo/shader/firefliesParticles/firefliesFrag.glsl"));

	_manager = std::shared_ptr<Graphics::ParticlesManager>(new Graphics::ParticlesManager(_physicsProgram, _displayProgram));
	_manager->loadTexture("../share/Demo/resources/textures/firework.png");
}

FirefliesEffect::~FirefliesEffect(void)
{
}

void FirefliesEffect::init(const glm::vec3 &position, GLuint numParticles)
{
	std::vector<Graphics::Particle> firefliesParticles(numParticles);
	for (unsigned int i = 0; i < numParticles; i++)
	{
		firefliesParticles[i].position = position;
		firefliesParticles[i].direction = glm::vec3(0.0f, -1.0f, 0.0f);
		firefliesParticles[i].velocity = 0.05f;
		firefliesParticles[i].life = (GLfloat)i * 100 / numParticles;
	}
	_manager->setParticles(firefliesParticles.data(), (GLsizei)firefliesParticles.size());
	this->setPosition(position);
}

void FirefliesEffect::setPosition(const glm::vec3 &pos)
{
	_manager->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesManager> &FirefliesEffect::getParticlesManager(void) const
{
	return _manager;
}

void FirefliesEffect::updateParticles(void) const
{
	_manager->updateParticles();
}