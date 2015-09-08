#ifndef TREE_HEADER
#define TREE_HEADER

#include <Engine/Graphics/Model/Static/StaticModel.hpp>

using namespace Engine;

class Tree
{
	std::shared_ptr<Graphics::ShaderProgram> _objectProgram;
	std::shared_ptr<Graphics::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Graphics::StaticModel> _model;
public:
	Tree(void);
	~Tree(void);
	const std::shared_ptr<Graphics::StaticModel> &getModel(void) const;
};

#endif