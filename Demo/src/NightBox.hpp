#ifndef NIGHTBOX_HEADER
#define NIGHTBOX_HEADER

#include <Engine/Graphics/SkyBox.hpp>

class NightBox
{
private:
	Engine::ShaderProgram *_skyboxProgram;
	Engine::SkyBox *_skybox;
public:
	NightBox(void);
	~NightBox(void);
	void display(const Engine::GBuffer &gbuf, const Engine::PerspCamera &cam) const;
};

#endif