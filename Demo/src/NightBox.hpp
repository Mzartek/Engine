#ifndef NIGHTBOX_HEADER
#define NIGHTBOX_HEADER

#include <Engine/Engine.hpp>

class NightBox
{
private:
	Engine::ShaderProgram *_skyboxProgram;
	Engine::SkyBox *_skybox;
public:
	NightBox(void);
	~NightBox(void);
	void display(Engine::GBuffer *gbuf, Engine::PerspCamera *cam) const;
};

#endif