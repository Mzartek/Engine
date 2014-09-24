#include <Engine/Screen.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Renderer.hpp>

engine::Screen::Screen()
{
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
	_colorBuffer = new Buffer;
}

engine::Screen::~Screen()
{
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
	delete _colorBuffer;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Screen::config(ShaderProgram *backgroundProgram, ShaderProgram *directProgram)
{
	_backgroundProgram = backgroundProgram;
	_directProgram = directProgram;

	// Create Vertex Buffer
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);

	// Create Color Buffer
	_colorBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::vec4), GL_DYNAMIC_DRAW);

	glBindVertexArray(_idVAO);  
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());  
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindVertexArray(0);

	glUseProgram(_backgroundProgram->getId());
	glUniform1i(glGetUniformLocation(_backgroundProgram->getId(), "materialTexture"), 0);
	glUniform1i(glGetUniformLocation(_backgroundProgram->getId(), "lightTexture"), 1);
	glUseProgram(0);

	glUseProgram(_directProgram->getId());
	glUniform1i(glGetUniformLocation(_directProgram->getId(), "backgroundTexture"), 0);
	glUseProgram(0);
}

#undef BUFFER_OFFSET

void engine::Screen::background(GBuffer *gbuf)
{
	gbuf->setBackgroundState();

	glUseProgram(_backgroundProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_LIGHT));

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	gbuf->clearLight();
}

void engine::Screen::display(Renderer *renderer, GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
{
	renderer->setState();

	glUseProgram(_directProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_BACKGROUND));

	glm::vec4 color(r, g, b, a);
	_colorBuffer->updateStoreMap(glm::value_ptr(color));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _colorBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);
}
