#include <Engine/TextArray.hpp>

engine::TextArray::TextArray(void)
{
	_idTexture = 0;
	_idVAO = 0;
	_idVBO = 0;
	_mat = new glm::mat4;
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
	
	delete _mat;

	TTF_CloseFont(_font);
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::TextArray::config(const GLchar *font, const GLuint &size,
	const GLubyte &r, const GLubyte &g, const GLubyte &b,
	const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer)
{
	SDL_Surface *t;
	
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = 0;
	
	_font = TTF_OpenFont(font, size);
	if(_font == NULL)
	{
		std::cerr << "Error while loading fontFile: " << font << std::endl;
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
		0, 1,

		(GLfloat)(x+w), (GLfloat)y,
		1, 1,

		(GLfloat)x, (GLfloat)(y+h),
		0, 0,

		(GLfloat)(x+w), (GLfloat)(y+h),
		1, 0
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
  
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));
	
	glBindVertexArray(0);

	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_textureLocation = glGetUniformLocation(_program->getId(), "textTex");

	*_mat = glm::ortho(0.0f, (GLfloat)renderer->getWidth(), 0.0f, (GLfloat)renderer->getHeight(), -1.0f, 1.0f);
}

void engine::TextArray::write(const GLchar *text)
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

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glUseProgram(_program->getId());
	glBindVertexArray(_idVAO);
	
	glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, glm::value_ptr(*_mat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idTexture);
	glUniform1i(_textureLocation, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindTexture(GL_TEXTURE0, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

#undef BUFFER_OFFSET
