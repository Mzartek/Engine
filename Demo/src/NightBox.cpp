#include "NightBox.hpp"

NightBox::NightBox(void)
{
	_skyboxProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/skybox/skyboxVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skybox/skyboxFrag.glsl"));

	_skybox = new_ptr(Engine::SkyBox(_skyboxProgram));

	_skybox->load(
		"../share/Demo/resources/textures/skybox/nnksky01_right.jpg", "../share/Demo/resources/textures/skybox/nnksky01_left.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_top.jpg", "../share/Demo/resources/textures/skybox/nnksky01_bottom.jpg",
		"../share/Demo/resources/textures/skybox/nnksky01_front.jpg", "../share/Demo/resources/textures/skybox/nnksky01_back.jpg");
}

NightBox::~NightBox(void)
{
	release_ptr(_skyboxProgram);
	release_ptr(_skybox);
}

void NightBox::display(Engine::GBuffer *gbuf, Engine::PerspCamera *cam) const
{
	_skybox->display(gbuf, cam);
}