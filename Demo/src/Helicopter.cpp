#include "Helicopter.hpp"

Helicopter::Helicopter()
{
	_objectProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_model = new_ptr(Engine::StaticModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/heli/corps.mobj");
	_model->sortMesh();
}

Helicopter::~Helicopter(void)
{
	release_ptr(_objectProgram);
	release_ptr(_depthMapProgram);
	release_ptr(_model);
}

Engine::StaticModel *Helicopter::getModel(void) const
{
	return _model;
}
