#ifndef CAMERA
#define CAMERA

#include "GLHead.hpp"
#include "ShaderProgram.hpp"

namespace engine
{
	class DLLAPI Camera
	{
	protected:
		Vector3D<GLfloat> *_pcamera;
		Vector3D<GLfloat> *_ptarget;
		GLuint _width;
		GLuint _height;
		GLfloat _projectionMatrix[16];
		GLfloat _VPMatrix[16];
	public:
		Camera(void);
		Camera(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		virtual ~Camera(void);
		void setPositionCamera(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setPositionTarget(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void setPerspective(const GLfloat &fov, const GLuint &width, const GLuint &height, const GLfloat &n, const GLfloat &f);
		Vector3D<GLfloat> getPositionCamera(void) const;
		Vector3D<GLfloat> getPositionTarget(void) const;
		GLuint getWidth(void) const;
		GLuint getHeight(void) const;
		GLfloat *getProjectionMatrix(void);
		GLfloat *getVPMatrix(void);
		void position(void);
	};
}

#endif
