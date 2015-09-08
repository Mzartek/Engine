#include "Tree.hpp"

Tree::Tree()
{
	_objectProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/object/objectVert.glsl",
		nullptr,
		nullptr,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl");

	_depthMapProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl");

	_model = std::make_shared<Graphics::StaticModel>(_objectProgram, _depthMapProgram);

	_model->loadFromFile("../share/Demo/resources/models/tree/Tree1.3ds");
	_model->sortMesh();
}

Tree::~Tree(void)
{
}

const std::shared_ptr<Graphics::StaticModel> &Tree::getModel(void) const
{
	return _model;
}
