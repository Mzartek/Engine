#ifndef BLOOMPOST_HEADER
#define BLOOMPOST_HEADER

#include <Engine/Graphics/Buffer/CBuffer.hpp>
#include <Engine/Graphics/Buffer/GBuffer.hpp>

#include <Engine/Graphics/ShaderProgram.hpp>

#define NUM_CBUFFER 10

using namespace Engine;

class BloomPost
{
	std::shared_ptr<Graphics::CBuffer> _cbuffer[NUM_CBUFFER];
	std::shared_ptr<Graphics::ShaderProgram> _copyProgram;
	std::shared_ptr<Graphics::ShaderProgram> _brightpassProgram;
	std::shared_ptr<Graphics::ShaderProgram> _gaussianProgram;

public:
	BloomPost(GLuint width, GLuint height);
	~BloomPost(void);

	void applyFilter(const std::shared_ptr<Graphics::GBuffer> &gbuf);
	const std::shared_ptr<Graphics::CBuffer> &getCBuffer(void);
};

#endif