#ifndef INPUTHANDLER_HEADER
#define INPUTHANDLER_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Input
	{
		class DLLAPI InputHandler
		{
			const GLubyte *_keyState;
			struct
			{
				GLint x;
				GLint y;
				GLuint buttons;
			} _mouseState;

		public:
			static InputHandler &Instance(void);

		private:
			InputHandler(void);
			~InputHandler(void);

		public:
			GLboolean getKeyBoardState(GLubyte button) const;
			GLboolean getMouseState(GLubyte button) const;
			GLint getMouseRelX(void) const;
			GLint getMouseRelY(void) const;
			void refresh(void);
		};
	}
}

#endif