#include "ArmySoldier.hpp"

ArmySoldier::ArmySoldier()
{
	_objectProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/skeletalObject/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/skeletalObject/objectGeom.glsl",
		"../share/Demo/shader/skeletalObject/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/skeletalDepthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skeletalDepthMap/depthMapFrag.glsl"));

	_model = std::shared_ptr<Engine::SkeletalModel>(new Engine::SkeletalModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/anim_model/nightwing_anim.dae", "Armature");
	_model->sortMesh();
}

ArmySoldier::~ArmySoldier(void)
{
}

const std::shared_ptr<Engine::SkeletalModel> &ArmySoldier::getModel(void) const
{
	return _model;
}
