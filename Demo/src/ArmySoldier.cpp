#include "ArmySoldier.hpp"

ArmySoldier::ArmySoldier()
{
	_objectProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/skeletalObject/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/skeletalObject/objectGeom.glsl",
		"../share/Demo/shader/skeletalObject/objectFrag.glsl");

	_depthMapProgram = new Engine::ShaderProgram(
		"../share/Demo/shader/skeletalDepthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skeletalDepthMap/depthMapFrag.glsl");

	_model = new Engine::SkeletalModel(_objectProgram, _depthMapProgram);

	_model->loadFromFile("../share/Demo/resources/models/anim_model/nightwing_anim.dae", "Armature");
	_model->sortMesh();
}

ArmySoldier::~ArmySoldier(void)
{
	delete _objectProgram;
	delete _depthMapProgram;
	delete _model;
}

Engine::SkeletalModel *ArmySoldier::getModel(void) const
{
	return _model;
}
