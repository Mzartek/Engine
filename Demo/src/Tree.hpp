#ifndef TREE_HEADER
#define TREE_HEADER

#include <Engine/Engine.hpp>

class Tree
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::Model *_model;
public:
	Tree(void);
	~Tree(void);
	Engine::Model *getModel(void) const;
};

#endif