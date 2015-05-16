#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Graphics/Renderer.hpp>
#include <Engine/Input/Input.hpp>
#include <Engine/Audio/Audio.hpp>
#include <Engine/Graphics/Window.hpp>

#include <Engine/Graphics/GBuffer.hpp>
#include <Engine/Graphics/DepthMap.hpp>
#include <Engine/Graphics/PerspCamera.hpp>
#include <Engine/Graphics/Octree.hpp>

#include "NightBox.hpp"
#include "Tree.hpp"
#include "AnimModel.hpp"
#include "Helicopter.hpp"
#include "Ground.hpp"
#include "MoonLight.hpp"
#include "ThunderLight.hpp"
#include "TorchLight.hpp"
#include "RainEffect.hpp"
#include "SmokeEffect.hpp"
#include "ExplosionEffect.hpp"
#include "TextDisplay.hpp"
#include "ScreenDisplay.hpp"

class Demo : public Engine::GameLoop
{
private:
	// System
	std::shared_ptr<Engine::Window> window;

	std::shared_ptr<Engine::GBuffer> gBuffer;
	std::vector<std::shared_ptr<Engine::DepthMap>> depthMaps;
	std::shared_ptr<Engine::PerspCamera> camera;

	std::shared_ptr<Engine::Octree> octree;
	std::set<Engine::Model *> object_display;

	std::shared_ptr<NightBox> nightBox;
	std::shared_ptr<Tree> tree;
	std::shared_ptr<AnimModel> animModel;
	std::shared_ptr<Helicopter> helicopter;
	std::shared_ptr<Ground> ground;
	std::shared_ptr<MoonLight> moonLight;
	std::shared_ptr<ThunderLight> thunderLight;
	std::shared_ptr<TorchLight> torchLight;
	std::shared_ptr<RainEffect> rainEffect;
	std::shared_ptr<SmokeEffect> smokeEffect;
	std::shared_ptr<ExplosionEffect> explosionEffect;
	std::shared_ptr<TextDisplay> textDisplay;
	std::shared_ptr<ScreenDisplay> screenDisplay;

	// Easy access
	std::shared_ptr<Engine::DirLight> moon_light;
	std::shared_ptr<Engine::DirLight> thunder_light;
	std::shared_ptr<Engine::SpotLight> torch_light;
	std::shared_ptr<Engine::ParticlesManager> rain_particles;
	std::shared_ptr<Engine::ParticlesManager> smoke_particles;
	std::shared_ptr<Engine::ParticlesManager> explosion_particles;
	std::shared_ptr<Engine::TextArray> text_display;
	std::shared_ptr<Engine::Screen> screen_display;
	std::shared_ptr<Engine::StaticModel> helicopter_model;
	std::shared_ptr<Engine::StaticModel> tree_model;

	// For the demo
	GLuint _step;
	GLuint _flash;
	bool _generateRandomFlash;
	glm::vec4 _screenColor;

	void manage_input(void);

public:
	Demo(const std::shared_ptr<Engine::Window> &w);
	~Demo(void);
	void display(GLfloat state);
	void state(long long time);
	void last_state(void);
	void reshape(GLuint w, GLuint h);
};




#endif
