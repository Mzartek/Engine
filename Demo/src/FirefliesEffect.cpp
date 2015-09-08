#include "FirefliesEffect.hpp"

FirefliesEffect::FirefliesEffect(void)
{
	const GLchar *varyings[] = { "outPosition", "outDirection", "outVelocity", "outLife" };

	_physicsProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/firefliesParticles/firefliesPhysics_v.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/firefliesParticles/firefliesPhysics_g.glsl",
		nullptr,
		varyings, static_cast<GLsizei>(sizeof(varyings) / sizeof(GLfloat *)));

	_displayProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/firefliesParticles/firefliesVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/firefliesParticles/firefliesGeom.glsl",
		"../share/Demo/shader/firefliesParticles/firefliesFrag.glsl");

	_particlesHandler = std::make_shared<Graphics::ParticlesHandler>(_physicsProgram, _displayProgram);
	_particlesHandler->loadTexture("../share/Demo/resources/textures/firework_yellow.png");
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
		firefliesParticles[i].life = static_cast<GLfloat>(i) * 100 / numParticles;
	}
	_particlesHandler->setParticles(firefliesParticles.data(), static_cast<GLsizei>(firefliesParticles.size()));
	this->setPosition(position);
}

void FirefliesEffect::setPosition(const glm::vec3 &pos)
{
	_particlesHandler->setPosition(pos);
}

const std::shared_ptr<Graphics::ParticlesHandler> &FirefliesEffect::getParticlesHandler(void) const
{
	return _particlesHandler;
}

void FirefliesEffect::updateParticles(void) const
{
	_particlesHandler->updateParticles();
}