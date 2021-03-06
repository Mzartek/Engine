#ifndef GROUND_HEADER
#define GROUND_HEADER

#include <Engine/Graphics/Model/Static/StaticModel.hpp>

using namespace Engine;

class Ground
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _objectProgram;
	std::shared_ptr<Graphics::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Graphics::Texture2D> _texture;
	std::shared_ptr<Graphics::Material> _material;
	std::shared_ptr<Graphics::StaticMesh> _mesh;
	std::shared_ptr<Graphics::StaticModel> _model;

public:
	Ground(void);
	~Ground(void);
	const std::shared_ptr<Graphics::StaticModel> &getModel(void) const;
};

#endif
