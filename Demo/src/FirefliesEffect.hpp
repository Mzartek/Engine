#ifndef FIREFLIESEFFECT_HEADER
#define FIREFLIESEFFECT_HEADER

#include <Engine/Graphics/ParticlesHandler.hpp>

using namespace Engine;

class FirefliesEffect
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _physicsProgram;
	std::shared_ptr<Graphics::ShaderProgram> _displayProgram;
	std::shared_ptr<Graphics::ParticlesHandler> _particlesHandler;

public:
	FirefliesEffect(void);
	~FirefliesEffect(void);
	void init(const glm::vec3 &position, GLuint numParticles);
	void setPosition(const glm::vec3 &pos);
	const std::shared_ptr<Graphics::ParticlesHandler> &getParticlesHandler(void) const;
	void updateParticles(void) const;
};

#endif