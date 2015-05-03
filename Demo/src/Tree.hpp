#ifndef TREE_HEADER
#define TREE_HEADER

#include <Engine/Graphics/StaticModel.hpp>

class Tree
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::StaticModel *_model;
public:
	Tree(void);
	~Tree(void);
	Engine::StaticModel *getModel(void) const;
};

#endif