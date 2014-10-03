#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Object.hpp"

namespace Engine
{
	class DLLAPI Input : public Object
	{
	private:
		const GLubyte *_keyState;
		struct MOUSESTATE
		{
			GLint x;
			GLint y;
			GLuint buttons;
		} _mouseState;
	public:
		Input(void);
		~Input(void);
		GLboolean getKeyBoardState(const GLubyte &button);
		GLboolean getMouseState(const GLubyte &button);
		GLint getMouseRelX(void);
		GLint getMouseRelY(void);
		void refresh(void);
	};
}

#endif