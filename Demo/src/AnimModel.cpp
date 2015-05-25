#include "AnimModel.hpp"

AnimModel::AnimModel()
{
	_objectProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/skeletalObject/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/skeletalObject/objectGeom.glsl",
		"../share/Demo/shader/skeletalObject/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/skeletalDepthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/skeletalDepthMap/depthMapFrag.glsl"));

	_model = std::shared_ptr<Graphics::SkeletalModel>(new Graphics::SkeletalModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/anim_model/nightwing_anim.dae", "Armature");
	_model->sortMesh();
}

AnimModel::~AnimModel(void)
{
}

const std::shared_ptr<Graphics::SkeletalModel> &AnimModel::getModel(void) const
{
	return _model;
}
