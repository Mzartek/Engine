#ifndef TREE_HEADER
#define TREE_HEADER

#include <Engine/Graphics/StaticModel.hpp>

class Tree
{
private:
	std::shared_ptr<Engine::ShaderProgram> _objectProgram;
	std::shared_ptr<Engine::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Engine::StaticModel> _model;
public:
	Tree(void);
	~Tree(void);
	const std::shared_ptr<Engine::StaticModel> &getModel(void) const;
};

#endif