#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Buffer : public Object
	{
	private:
		GLenum _target;
		GLuint _idBuffer;
		GLsizeiptr _size;
	public:
		Buffer(void);
		~Buffer(void);
		GLenum getTarget(void) const;
		GLuint getId(void) const;
		void createStore(GLenum target, const GLvoid *data, GLsizeiptr size, GLenum usage);
		void updateStoreSub(const GLvoid *data) const;
		void updateStoreMap(const GLvoid *data) const;
	};
}

#endif