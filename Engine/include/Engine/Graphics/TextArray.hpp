#ifndef TEXTARRAY_HEADER
#define TEXTARRAY_HEADER

#include "../Object.hpp"

#include "Texture2D.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"

namespace Engine
{
	class DLLAPI TextArray : public Object
	{
	private:
		TTF_Font *_font;
		std::shared_ptr<Texture2D> _texture;
		std::shared_ptr<Buffer> _vertexBuffer;
		std::shared_ptr<Buffer> _MVPMatrixBuffer;
		glm::mat4 _mat;
		std::shared_ptr<ShaderProgram> _program;
		GLuint _idVAO;
		SDL_Color _color;

	public:
		TextArray(const std::shared_ptr<ShaderProgram> &program);
		~TextArray(void);
		void setFont(const GLchar *font, GLuint size, GLubyte r, GLubyte g, GLubyte b);
		void writeScreen(GLuint x, GLuint y, GLuint w, GLuint h, const std::shared_ptr<Window> &window, const GLchar *text);
		void writeScreen(const GLchar *text) const;
		void display(const std::shared_ptr<Window> &window) const;
	};
}

#endif
