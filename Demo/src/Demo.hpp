#ifndef DEMO_HEADER
#define DEMO_HEADER

#include <Engine/Audio/AudioRenderer.hpp>
#include <Engine/Graphics/GraphicsRenderer.hpp>
#include <Engine/Input/InputHandler.hpp>

#include <Engine/Graphics/Buffer/DepthMap.hpp>
#include <Engine/Graphics/Buffer/GBuffer.hpp>

#include <Engine/Graphics/Camera/FreeCam.hpp>

#include <Engine/Graphics/Octree.hpp>

#include "AnimModel.hpp"
#include "BloomPost.hpp"
#include "ExplosionEffect.hpp"
#include "FirefliesEffect.hpp"
#include "Ground.hpp"
#include "Helicopter.hpp"
#include "MoonLight.hpp"
#include "RainEffect.hpp"
#include "NightBox.hpp"
#include "SmokeEffect.hpp"
#include "TextDisplay.hpp"
#include "ThunderLight.hpp"
#include "TorchLight.hpp"
#include "Tree.hpp"

using namespace Engine;

class Demo : public Graphics::GameLoop
{
private:
	std::shared_ptr<Graphics::ShaderProgram> backgroundProgram;
	std::shared_ptr<Graphics::ShaderProgram> windowProgram;

	std::shared_ptr<Graphics::GBuffer> gbuffer;

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
	std::shared_ptr<BloomPost> bloomPost;

	std::vector<std::shared_ptr<Graphics::DepthMap>> depthMaps;

	std::set<Graphics::Model *> object_display;

	void manage_input(void);

public:
	Demo(void);
	~Demo(void);
	void display(GLfloat state);
	void state(long long time);
	void last_state(void);
	void reshape(GLuint w, GLuint h);
	void launch(void);
};




#endif
