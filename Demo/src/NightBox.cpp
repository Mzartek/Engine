#include "NightBox.hpp"

NightBox::NightBox(void)
{
	_skyboxProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/skybox/skyboxVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/skybox/skyboxFrag.glsl");

	_skybox = std::make_shared<Graphics::SkyBox>(_skyboxProgram);

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