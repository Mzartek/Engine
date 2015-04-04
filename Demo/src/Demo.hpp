#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <ctime>

#include <Engine/Renderer.hpp>
#include <Engine/Audio.hpp>
#include <Engine/Input.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/DepthMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/SkyBox.hpp>
#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/SpotLight.hpp>
#include <Engine/ParticlesManager.hpp>
#include <Engine/Screen.hpp>
#include <Engine/TextArray.hpp>
#include <Engine/OctreeSystem.hpp>
#include <Engine/Sound.hpp>

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
	Engine::ShaderProgram *mushroomProgram;
	Engine::ShaderProgram *dirLightProgram;
	Engine::ShaderProgram *spotLightProgram;
	Engine::ShaderProgram *depthMapProgram;
	Engine::ShaderProgram *displayRainProgram;
	Engine::ShaderProgram *displaySmokeProgram;
	Engine::ShaderProgram *backgroundProgram;
	Engine::ShaderProgram *screenProgram;
	Engine::ShaderProgram *textProgram;

	Engine::ShaderProgram *physicsRainProgram;
	Engine::ShaderProgram *physicsSmokeProgram;

	Engine::GBuffer *gBuffer;
	Engine::DepthMap *dMaps;
	Engine::FreeCam *camera;
	Engine::SkyBox *skybox;
	Engine::Model *sol;
	Engine::Model *model_tree;
	Engine::DirLight *moon;
	Engine::SpotLight *torch;
	Engine::ParticlesManager *rainManager;
	Engine::ParticlesManager *smokeManager;
	Engine::Screen *screen;
	Engine::TextArray *text;

	Engine::OctreeSystem *octreeSystem;

	// Sound
	Engine::Sound *rain_sound;
	Engine::Sound *fire_sound;

	// Private methods
	void configSol(void);
	void configRainParticles(void);
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
