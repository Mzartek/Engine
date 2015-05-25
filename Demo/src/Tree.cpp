#include "Tree.hpp"

Tree::Tree()
{
	_objectProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_model = std::shared_ptr<Graphics::StaticModel>(new Graphics::StaticModel(_objectProgram, _depthMapProgram));

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
