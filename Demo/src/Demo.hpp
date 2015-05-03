#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Graphics/Renderer.hpp>
#include <Engine/Input/Input.hpp>
#include <Engine/Audio/Audio.hpp>

#include <Engine/Graphics/GBuffer.hpp>
#include <Engine/Graphics/DepthMap.hpp>
#include <Engine/Graphics/FreeCam.hpp>
#include <Engine/Graphics/Octree.hpp>

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

	Engine::Octree *octree;

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
