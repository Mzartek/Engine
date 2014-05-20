#include <Engine/Screen.hpp>

engine::Screen::Screen()
{
	_program = NULL;
}

engine::Screen::~Screen()
{
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
}

#define BUFFER_OFFSET(i) ((GLubyte *)NULL + (i))

void engine::Screen::init(ShaderProgram *program)
{
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1,  1,
		1,  1
	};
  
	_program = program;

	_colorLocation = glGetUniformLocation(_program->getId(), "color");

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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, GLsizei(2*sizeof(GLfloat)), BUFFER_OFFSET(0));

	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Screen::display(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	if(_program==NULL)
	{
		std::cerr << "Can't diplay Screen without initialisation" << std::endl;
		return;
	}
  
	glDepthMask(GL_FALSE);
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);

	glUniform4f(_colorLocation, r, g, b, a);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthMask(GL_TRUE);
}
