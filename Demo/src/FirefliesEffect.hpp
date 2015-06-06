#ifndef FIREFLIESEFFECT_HEADER
#define FIREFLIESEFFECT_HEADER

#include <Engine/Graphics/ParticlesManager.hpp>

using namespace Engine;

class FirefliesEffect
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _physicsProgram;
	std::shared_ptr<Graphics::ShaderProgram> _displayProgram;
	std::shared_ptr<Graphics::ParticlesManager> _manager;

public:
	FirefliesEffect(void);
	~FirefliesEffect(void);
	void init(const glm::vec3 &position, GLuint numParticles);
	void setPosition(const glm::vec3 &pos);
	const std::shared_ptr<Graphics::ParticlesManager> &getParticlesManager(void) const;
	void updateParticles(void) const;
};

#endif