#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Engine.hpp>
#include <ctime>

#include "NightBox.hpp"
#include "Tree.hpp"
#include "ArmySoldier.hpp"
#include "Helicopter.hpp"
#include "Ground.hpp"
#include "MoonLight.hpp"
#include "TorchLight.hpp"
#include "RainEffect.hpp"
#include "SmokeEffect.hpp"
#include "TextDisplay.hpp"
#include "ScreenDisplay.hpp"

class Demo : public Engine::GameLoop
{
private:
	// System
	Engine::Renderer *renderer;
	Engine::Input *input;
	Engine::Audio *audio;

	Engine::GBuffer *gBuffer;
	Engine::DepthMap *dMaps;
	Engine::FreeCam *camera;

	Engine::OctreeSystem *octreeSystem;

	NightBox *nightBox;
	Tree *tree;
	ArmySoldier *armySoldier;
    Helicopter *helicopter;
	Ground *ground;
	MoonLight *moonLight;
	TorchLight *torchLight;
	RainEffect *rainEffect;
	SmokeEffect *smokeEffect;
	TextDisplay *textDisplay;
	ScreenDisplay *screenDisplay;

public:
	Demo(Engine::Renderer *r, Engine::Input *i, Engine::Audio *a);
	~Demo(void);
	void display(GLfloat state);
	void idle(long long time);
	void reshape(GLuint w, GLuint h);
	void launch(void);
};




#endif
