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
	std::shared_ptr<Engine::Renderer> renderer;
	std::shared_ptr<Engine::Input> input;
	std::shared_ptr<Engine::Audio> audio;

	std::unique_ptr<Engine::GBuffer> gBuffer;
	std::unique_ptr<std::array<std::unique_ptr<Engine::DepthMap>, CSM_NUM>> array_depthMap;
	std::unique_ptr<Engine::FreeCam> camera;

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
	Demo(std::shared_ptr<Engine::Renderer> r, std::shared_ptr<Engine::Input> i, std::shared_ptr<Engine::Audio> a);
	~Demo(void);
	void display(GLfloat state);
	void idle(long long time);
	void reshape(GLuint w, GLuint h);
	void launch(void);
};




#endif
