#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Engine.hpp>
#include <ctime>

#include "RainEffect.hpp"

class Demo : public Engine::GameLoop
{
private:
	// System
	Engine::Renderer *renderer;
	Engine::Input *input;
	Engine::Audio *audio;

	// ShaderProgram
	Engine::ShaderProgram *skyboxProgram;
	Engine::ShaderProgram *objectProgram;
	Engine::ShaderProgram *dirLightProgram;
	Engine::ShaderProgram *spotLightProgram;
	Engine::ShaderProgram *depthMapProgram;
	Engine::ShaderProgram *displaySmokeProgram;
	Engine::ShaderProgram *backgroundProgram;
	Engine::ShaderProgram *screenProgram;
	Engine::ShaderProgram *textProgram;

	Engine::ShaderProgram *physicsSmokeProgram;

	Engine::GBuffer *gBuffer;
	Engine::DepthMap *dMaps;
	Engine::FreeCam *camera;
	Engine::SkyBox *skybox;
	Engine::Model *sol;
	Engine::Model *model_tree;
	Engine::DirLight *moon;
	Engine::SpotLight *torch;
	Engine::ParticlesManager *smokeManager;
	Engine::Screen *screen;
	Engine::TextArray *text;

	Engine::OctreeSystem *octreeSystem;

	RainEffect *rainEffect;

	// Sound
	Engine::Sound *rain_sound;
	Engine::Sound *fire_sound;

	// Private methods
	void configSol(void);
	void configSmokeParticles(void);
	void configTree(void);
	void updateRainParticles(void);
public:
	Demo(Engine::Renderer *r, Engine::Input *i, Engine::Audio *a);
	~Demo(void);
	void display(GLfloat state);
	void idle(long long time);
	void reshape(GLuint w, GLuint h);
	void launch(void);
};




#endif
