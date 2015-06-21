#ifndef BLOOMPOST_HEADER
#define BLOOMPOST_HEADER

#include <Engine/Graphics/GBuffer.hpp>
#include <Engine/Graphics/CBuffer.hpp>
#include <Engine/Graphics/ShaderProgram.hpp>
#include <Engine/Graphics/PostProcessing.hpp>

#define NUM_CBUFFER 10

using namespace Engine;

class BloomPost
{
private:
	std::shared_ptr<Graphics::CBuffer> _cbuffer[NUM_CBUFFER];
	std::shared_ptr<Graphics::ShaderProgram> _copyProgram;
	std::shared_ptr<Graphics::ShaderProgram> _brightpassProgram;
	std::shared_ptr<Graphics::ShaderProgram> _gaussianProgram;
	std::shared_ptr<Graphics::PostProcessing> _copyProcessing;
	std::shared_ptr<Graphics::PostProcessing> _brightpassProcessing;
	std::shared_ptr<Graphics::PostProcessing> _gaussianProcessing;

public:
	BloomPost(GLuint width, GLuint height);
	~BloomPost(void);

	void applyFilter(const std::shared_ptr<Graphics::GBuffer> &gbuf);
	GLuint getTextureId(void);
};

#endif