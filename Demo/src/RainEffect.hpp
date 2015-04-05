#ifndef RAINEFFECT_HEADER
#define RAINEFFECT_HEADER

#include <Engine/Engine.hpp>

class RainEffect
{
private:
	glm::vec3 *_direction;
	Engine::ShaderProgram *_physicsRainProgram;
	Engine::ShaderProgram *_displayRainProgram;
	Engine::ParticlesManager *_rainManager;
public:
	RainEffect(void);
	~RainEffect(void);
	void init(const glm::vec3 &position, const unsigned int &numParticles);
	void setDirection(const glm::vec3 &direction);
	void updateParticles(const glm::vec3 &position);
	void display(Engine::GBuffer *gbuf, Engine::Camera *cam);
};

#endif