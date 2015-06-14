#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Graphics/GraphicsRenderer.hpp>
#include <Engine/Audio/AudioRenderer.hpp>
#include <Engine/Input/InputManager.hpp>

#include <Engine/Graphics/Window.hpp>
#include <Engine/Graphics/GBuffer.hpp>
#include <Engine/Graphics/DepthMap.hpp>
#include <Engine/Graphics/FreeCam.hpp>
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
#include "FirefliesEffect.hpp"
#include "TextDisplay.hpp"
#include "ScreenDisplay.hpp"

using namespace Engine;

class Demo : public Graphics::GameLoop
{
private:
		Graphics::GraphicsRenderer &graphicsRenderer;
		Audio::AudioRenderer &audioRenderer;
		Input::InputManager &inputManager;

		// System
		std::shared_ptr<Graphics::Window> window;

		std::shared_ptr<Graphics::GBuffer> gBuffer;
		std::shared_ptr<Graphics::FreeCam> camera;

		std::shared_ptr<Graphics::Octree> octree;

		std::shared_ptr<NightBox> nightBox;
		std::shared_ptr<Tree> tree;
		std::shared_ptr<AnimModel> animModel;
		std::shared_ptr<Ground> ground;
		std::shared_ptr<MoonLight> moonLight;
		std::shared_ptr<TorchLight> torchLight;
		std::shared_ptr<RainEffect> rainEffect;
		std::shared_ptr<SmokeEffect> smokeEffect;
		std::shared_ptr<ScreenDisplay> screenDisplay;

		// Easy access
		std::shared_ptr<Graphics::DirLight> moon_light;
		std::shared_ptr<Graphics::SpotLight> torch_light;
		std::shared_ptr<Graphics::ParticlesManager> rain_particles;
		std::shared_ptr<Graphics::ParticlesManager> smoke_particles;
		std::shared_ptr<Graphics::Screen> screen_display;
		std::shared_ptr<Graphics::StaticModel> tree_model;

		std::vector<std::shared_ptr<Graphics::DepthMap>> depthMaps;

		std::set<Graphics::Model *> object_display;

		void manage_input(void);

public:
		Demo(const std::shared_ptr<Graphics::Window> &w);
		~Demo(void);
		void display(GLfloat state);
		void state(long long time);
		void last_state(void);
		void reshape(GLuint w, GLuint h);
};




#endif
