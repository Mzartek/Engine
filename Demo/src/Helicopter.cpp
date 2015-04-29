#include "Helicopter.hpp"

Helicopter::Helicopter()
{
	_objectProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl");

	_depthMapProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl");

	_model = new Engine::StaticModel(_objectProgram, _depthMapProgram);

	_model->loadFromFile("../share/Demo/resources/models/heli/corps.mobj");
	_model->sortMesh();
}

Helicopter::~Helicopter(void)
{
	delete _objectProgram;
	delete _depthMapProgram;
	delete _model;
}

Engine::StaticModel *Helicopter::getModel(void) const
{
	return _model;
}
