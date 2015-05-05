#ifndef NIGHTBOX_HEADER
#define NIGHTBOX_HEADER

#include <Engine/Graphics/SkyBox.hpp>

class NightBox
{
private:
	std::shared_ptr<Engine::ShaderProgram> _skyboxProgram;
	std::shared_ptr<Engine::SkyBox> _skybox;
public:
	NightBox(void);
	~NightBox(void);
	void display(const std::shared_ptr<Engine::GBuffer> &gbuf, const std::shared_ptr<Engine::PerspCamera> &cam) const;
};

#endif