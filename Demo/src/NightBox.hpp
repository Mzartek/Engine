#ifndef NIGHTBOX_HEADER
#define NIGHTBOX_HEADER

#include <Engine/Graphics/SkyBox.hpp>

using namespace Engine;

class NightBox
{
	std::shared_ptr<Graphics::ShaderProgram> _skyboxProgram;
	std::shared_ptr<Graphics::SkyBox> _skybox;

public:
	NightBox(void);
	~NightBox(void);
	void display(const std::shared_ptr<Graphics::GBuffer> &gbuf, const std::shared_ptr<Graphics::PerspCamera> &cam) const;
};

#endif