#include <Engine/Screen.hpp>

engine::Screen::Screen()
{
	_backgroundProgram = NULL;
	_directProgram = NULL;
}

engine::Screen::~Screen()
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Screen::config(ShaderProgram *backgroundProgram, ShaderProgram *directProgram)
{
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1,
	};
	
	_backgroundProgram = backgroundProgram;
	_bMaterialTextureLocation = glGetUniformLocation(_backgroundProgram->getId(), "materialTexture");
	_bLightTextureLocation = glGetUniformLocation(_backgroundProgram->getId(), "lightTexture");

	_directProgram = directProgram;
	_dBackgroundTextureLocation = glGetUniformLocation(_directProgram->getId(), "backgroundTexture");
	_dColorLocation = glGetUniformLocation(_directProgram->getId(), "color");
	
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertex, vertex, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), BUFFER_OFFSET(0));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Screen::background(GBuffer *gbuf)
{
	gbuf->setBackgroundConfig();

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

	gbuf->clearLight();
}

void engine::Screen::display(Renderer *renderer, GBuffer *gbuf, const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
{ 
	renderer->setConfig();

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
