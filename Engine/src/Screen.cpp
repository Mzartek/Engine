#include <Engine/Screen.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Renderer.hpp>

engine::Screen::Screen()
{
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
}

engine::Screen::~Screen()
{
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Screen::config(ShaderProgram *backgroundProgram, ShaderProgram *directProgram)
{
	_backgroundProgram = backgroundProgram;
	_directProgram = directProgram;

	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);

	glBindVertexArray(_idVAO);
  
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
  
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), BUFFER_OFFSET(0));

	glBindVertexArray(0);

	_bMaterialTextureLocation = glGetUniformLocation(_backgroundProgram->getId(), "materialTexture");
	_bLightTextureLocation = glGetUniformLocation(_backgroundProgram->getId(), "lightTexture");

	_dBackgroundTextureLocation = glGetUniformLocation(_directProgram->getId(), "backgroundTexture");
	_dColorLocation = glGetUniformLocation(_directProgram->getId(), "color");
}

#undef BUFFER_OFFSET

void engine::Screen::background(GBuffer *gbuf)
{
	gbuf->setBackgroundState();

	glUseProgram(_backgroundProgram->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));
	glUniform1i(_bMaterialTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_LIGHT));
	glUniform1i(_bLightTextureLocation, 1);

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
	glUniform1i(_dBackgroundTextureLocation, 0);

	glUniform4f(_dColorLocation, r, g, b, a);

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);
}
