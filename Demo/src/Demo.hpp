#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Graphics/Renderer.hpp>
#include <Engine/Input/Input.hpp>
#include <Engine/Audio/Audio.hpp>
#include <Engine/Graphics/Window.hpp>

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
	std::shared_ptr<Engine::Window> window;

	std::shared_ptr<Engine::GBuffer> gBuffer;
	std::vector<std::shared_ptr<Engine::DepthMap>> depthMaps;
	std::shared_ptr<Engine::FreeCam> camera;

	std::shared_ptr<Engine::Octree> octree;

	std::shared_ptr<NightBox> nightBox;
	std::shared_ptr<Tree> tree;
	std::shared_ptr<ArmySoldier> armySoldier;
	std::shared_ptr<Helicopter> helicopter;
	std::shared_ptr<Ground> ground;
	std::shared_ptr<MoonLight> moonLight;
	std::shared_ptr<TorchLight> torchLight;
	std::shared_ptr<RainEffect> rainEffect;
	std::shared_ptr<SmokeEffect> smokeEffect;
	std::shared_ptr<TextDisplay> textDisplay;
	std::shared_ptr<ScreenDisplay> screenDisplay;

public:
	Demo(const std::shared_ptr<Engine::Window> &w);
	~Demo(void);
	void display(GLfloat state);
	void idle(long long time);
	void reshape(GLuint w, GLuint h);
};




#endif
