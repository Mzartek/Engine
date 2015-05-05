#ifndef GROUND_HEADER
#define GROUND_HEADER

#include <Engine/Graphics/ShaderProgram.hpp>
#include <Engine/Graphics/StaticModel.hpp>

class Ground
{
private:
	std::shared_ptr<Engine::ShaderProgram> _objectProgram;
	std::shared_ptr<Engine::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Engine::Texture2D> _texture;
	std::shared_ptr<Engine::Material> _material;
	std::shared_ptr<Engine::StaticMesh> _mesh;
	std::shared_ptr<Engine::StaticModel> _model;
public:
	Ground(void);
	~Ground(void);
	const std::shared_ptr<Engine::StaticModel> &getModel(void) const;
};

#endif
