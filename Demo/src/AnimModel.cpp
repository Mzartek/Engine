#include "AnimModel.hpp"

AnimModel::AnimModel()
{
	_objectProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/skeletalObject/objectVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/skeletalObject/objectGeom.glsl",
		"../share/Demo/shader/skeletalObject/objectFrag.glsl");

	_depthMapProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/skeletalDepthMap/depthMapVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/skeletalDepthMap/depthMapFrag.glsl");

	_model = std::make_shared<Graphics::SkeletalModel>(_objectProgram, _depthMapProgram);

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
