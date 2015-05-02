#include "ArmySoldier.hpp"

ArmySoldier::ArmySoldier()
{
	_objectProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/skeletalObject/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/skeletalObject/objectGeom.glsl",
		"../share/Demo/shader/skeletalObject/objectFrag.glsl"));

	_depthMapProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/skeletalDepthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skeletalDepthMap/depthMapFrag.glsl"));

	_model = new_ref(Engine::SkeletalModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/anim_model/nightwing_anim.dae", "Armature");
	_model->sortMesh();
}

ArmySoldier::~ArmySoldier(void)
{
	release_ref(_objectProgram);
	release_ref(_depthMapProgram);
	release_ref(_model);
}

Engine::SkeletalModel *ArmySoldier::getModel(void) const
{
	return _model;
}
