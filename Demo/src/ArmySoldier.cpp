#include "ArmySoldier.hpp"

ArmySoldier::ArmySoldier()
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

	//_model->loadFromFile("../share/Demo/resources/models/ArmyPilot/ArmyPilot.bvh");
	_model->sortMesh();
}

ArmySoldier::~ArmySoldier(void)
{
	delete _objectProgram;
	delete _depthMapProgram;
	delete _model;
}

Engine::StaticModel *ArmySoldier::getModel(void) const
{
	return _model;
}
