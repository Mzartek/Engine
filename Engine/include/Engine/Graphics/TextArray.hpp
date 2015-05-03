#ifndef TEXTARRAY_HEADER
#define TEXTARRAY_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "Texture2D.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "Renderer.hpp"

namespace Engine
{
	class DLLAPI TextArray : public Object
	{
	private:
		TTF_Font *_font;
		Texture2D *_texture;
		Buffer *_vertexBuffer;
		Buffer *_MVPMatrixBuffer;
		glm::mat4 *_mat;
		ShaderProgram *_program;
		GLuint _idVAO;
		SDL_Color _color;
	public:
		TextArray(ShaderProgram *program);
		~TextArray(void);
		void setFont(const GLchar *font, const GLuint &size, const GLubyte &r, const GLubyte &g, const GLubyte &b);
		void writeScreen(const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, Renderer *renderer, const GLchar *text) const;
		void writeScreen(const GLchar *text) const;
		void display(Renderer *renderer) const;
	};
}

#endif
