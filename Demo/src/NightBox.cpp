#include "NightBox.hpp"

NightBox::NightBox(void)
{
	_skyboxProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/skybox/skyboxVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skybox/skyboxFrag.glsl"));

	_skybox = std::shared_ptr<Graphics::SkyBox>(new Graphics::SkyBox(_skyboxProgram));

	_skybox->load(
		"../share/Demo/resources/textures/skybox/nnksky01_right.jpg", "../share/Demo/resources/textures/skybox/nnksky01_left.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_top.jpg", "../share/Demo/resources/textures/skybox/nnksky01_bottom.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_front.jpg", "../share/Demo/resources/textures/skybox/nnksky01_back.jpg");
}

NightBox::~NightBox(void)
{
}

void NightBox::display(const std::shared_ptr<Graphics::GBuffer> &gbuf, const std::shared_ptr<Graphics::PerspCamera> &cam) const
{
	_skybox->display(gbuf, cam);
}