#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "ShaderProgram.hpp"
#include "Renderer.hpp"

namespace engine
{
	class DLLAPI TextArray : public Object
	{
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		glm::mat4 *_mat;
		// Do not delete it
		ShaderProgram *_program;
		// Location or Index
		GLint _MVPLocation;
		GLint _textureLocation;
		// SDL Feature
		TTF_Font *_font;
		SDL_Color _color;
	public:
		TextArray(void);
		~TextArray(void);
		void config(const GLchar *font, const GLuint &size,
			const GLubyte &r, const GLubyte &g, const GLubyte &b,
			const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer);
		void write(const GLchar *text);
		void display(Renderer *renderer);
	};
}

#endif
