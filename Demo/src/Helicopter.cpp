#include "Helicopter.hpp"

Helicopter::Helicopter()
{
	_objectProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_model = std::shared_ptr<Engine::StaticModel>(new Engine::StaticModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/heli/corps.mobj");
	_model->sortMesh();
}

Helicopter::~Helicopter(void)
{
}

const std::shared_ptr<Engine::StaticModel> &Helicopter::getModel(void) const
{
	return _model;
}
