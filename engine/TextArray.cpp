#include <Engine/TextArray.hpp>

engine::TextArray::TextArray(void)
{
	_idTexture = 0;
	_idVAO = 0;
	_idVBO = 0;
	_program = NULL;
}

engine::TextArray::~TextArray(void)
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);

	TTF_CloseFont(_font);
}

#define BUFFER_OFFSET(i) ((GLubyte *)NULL + (i))

void engine::TextArray::config(const std::string fontFile, GLuint size,
			       GLubyte r, GLubyte g, GLubyte b,
			       GLuint x, GLuint y, GLuint w, GLuint h, ShaderProgram *program, Window *window)
{
	SDL_Surface *t;
	
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = 0;
	
	_font = TTF_OpenFont(&fontFile[0], size);
	if(_font == NULL)
	{
		std::cerr << "Error while loading fontFile: " << fontFile << std::endl;
		exit(1);
	}
	t = TTF_RenderText_Blended(_font, " ", _color);
	if(t == NULL)
	{
		std::cerr << "Error while creating RenderText" << std::endl;
		exit(1);
	}
	loadTextureFromSDL_Surface(t, &_idTexture);
	SDL_FreeSurface(t);
	
	GLfloat vertexArray[] = {
		(GLfloat)x, (GLfloat)y,
		0, 0,

		(GLfloat)(x+w), (GLfloat)y,
		1, 0,

		(GLfloat)x, (GLfloat)(y+h),
		0, 1,

		(GLfloat)(x+w), (GLfloat)(y+h),
		1, 1
	};
  
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
  
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertexArray, vertexArray, GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
  
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, GLsizei(4*sizeof(GLfloat)), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GLsizei(4*sizeof(GLfloat)), BUFFER_OFFSET(2*sizeof(GLfloat)));
	
	glBindVertexArray(0);

	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_textureLocation = glGetUniformLocation(_program->getId(), "textTex");

	matrixOrtho(_mat, 0, (GLfloat)window->getWidth(), 0, (GLfloat)window->getHeight(), -1, 1);
}

void engine::TextArray::write(const std::string text)
{
	SDL_Surface *t;
	
	t = TTF_RenderText_Blended(_font, &text[0], _color);
	if(t == NULL)
	{
		std::cerr << "Error while creating RenderText" << std::endl;
		exit(1);
	}
	
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	loadTextureFromSDL_Surface(t, &_idTexture);
	
	SDL_FreeSurface(t);
}

void engine::TextArray::display(void)
{
	if(_program == NULL)
	{
		std::cerr << "You need to configure the TextArray before" << std::endl;
		return;
	}
	
	glDepthMask(GL_FALSE);
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);
	
	glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, _mat);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(_textureLocation, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindTexture(GL_TEXTURE0, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthMask(GL_TRUE);
}

#undef BUFFER_OFFSET
