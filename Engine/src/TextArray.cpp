#include <Engine/TextArray.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/Renderer.hpp>

engine::TextArray::TextArray(void)
	: _font(NULL)
{
	_texture = new Texture;
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
	_MVPMatrixBuffer = new Buffer;
	_mat = new glm::mat4;
}

engine::TextArray::~TextArray(void)
{
	if (_font) TTF_CloseFont(_font);
	delete _texture;
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
	delete _MVPMatrixBuffer;
	delete _mat;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::TextArray::config(const GLchar *font, const GLuint &size,
	const GLubyte &r, const GLubyte &g, const GLubyte &b,
	const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer)
{
	SDL_Surface *t;

	_program = program;

	if (_font) TTF_CloseFont(_font);
	
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
	_texture->load2DTextureFromSDL_Surface(t);
	SDL_FreeSurface(t);
	
	GLfloat vertexArray[] = {
		(GLfloat)x, (GLfloat)y,
		0, 0,

		(GLfloat)x+w, (GLfloat)y,
		1, 0,

		(GLfloat)x, (GLfloat)y+h,
		0, 1,

		(GLfloat)x+w, (GLfloat)y+h,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertexArray, sizeof vertexArray, GL_STATIC_DRAW);
	_MVPMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof glm::mat4, GL_DYNAMIC_DRAW);

	glBindVertexArray(_idVAO);  
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);  
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), BUFFER_OFFSET(2*sizeof(GLfloat)));
	glBindVertexArray(0);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "textTex"), 0);
	glUseProgram(0);

	*_mat = glm::ortho(0.0f, (GLfloat)renderer->getWidth(), 0.0f, (GLfloat)renderer->getHeight(), -1.0f, 1.0f);
}

#undef BUFFER_OFFSET

void engine::TextArray::write(const GLchar *text)
{
	SDL_Surface *t;
	
	t = TTF_RenderText_Blended(_font, &text[0], _color);
	if(t == NULL)
	{
		std::cerr << "Error while creating RenderText" << std::endl;
		exit(1);
	}
	_texture->load2DTextureFromSDL_Surface(t);
	
	SDL_FreeSurface(t);
}

void engine::TextArray::display(Renderer *renderer)
{
	renderer->setState();

	glUseProgram(_program->getId());

	_MVPMatrixBuffer->updateStoreMap(glm::value_ptr(*_mat));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _MVPMatrixBuffer->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);
}
