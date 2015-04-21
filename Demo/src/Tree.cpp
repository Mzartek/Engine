#include "Tree.hpp"

Tree::Tree()
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

	_model = new Engine::Model(_objectProgram, _depthMapProgram);
	
	_model->loadFromFile("../share/Demo/resources/models/tree/Tree1.3ds");
	_model->sortMesh();
}

Tree::~Tree(void)
{
	delete _objectProgram;
	delete _depthMapProgram;
	delete _model;
}

Engine::Model *Tree::getModel(void) const
{
	return _model;
}
