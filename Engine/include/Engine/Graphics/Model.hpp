#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "../Object.hpp"
#include "../Tools/StringManager.hpp"

#include "Mesh.hpp"
#include "Buffer.hpp"
#include "ShaderProgram.hpp"
#include "GBuffer.hpp"
#include "PerspCamera.hpp"
#include "DirLight.hpp"
#include "SpotLight.hpp"
#include "DepthMap.hpp"
#include "TextureCube.hpp"

namespace Engine
{
	class DLLAPI Model : public Object
	{
	private:
		glm::vec3 *_position;
		glm::vec3 *_scale;
		glm::quat *_rotation;

		GLboolean _needMatModel;
		GLboolean _needMatNormal;

		void genMatModel(void) const;
		void genMatNormal(void) const; 

	protected:
		struct
		{
			glm::vec3 ALIGN(16) position;
			glm::vec3 ALIGN(16) forward;
			glm::vec3 ALIGN(16) left;
			glm::vec3 ALIGN(16) up;
		} _camera;

		GLboolean _isMirror;

		std::vector<Mesh *> *_tMesh;

		Buffer *_matrixBuffer;
		Buffer *_cameraBuffer;

		glm::mat4 *_modelMatrix;
		glm::mat4 *_normalMatrix;

		TextureCube *_cubeTexture;

		ShaderProgram *_gProgram;
		ShaderProgram *_smProgram;

		void checkMatrix(void);

	public:
		Model(ShaderProgram *gProgram, ShaderProgram *smProgram);
		Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
		~Model(void);

		void addMesh(Mesh *mesh);
		void sortMesh(void);
		void setPosition(const glm::vec3 &position);
		void setScale(const glm::vec3 &scale);
		void setRotation(const glm::vec3 &rotation);
		void setRotation(const glm::vec3 &axis, const GLfloat &angle);
		void setCubeTexture(TextureCube *cubeTexture);
		glm::vec3 getPosition(void) const;
		glm::vec3 getScale(void) const;
		std::pair<glm::vec3, GLfloat> getAxisAngleRotation(void) const;
		Mesh *getMesh(const GLuint &num) const;

		virtual void display(const GBuffer &gbuf, const PerspCamera &cam) = 0;
		virtual void displayTransparent(const GBuffer &gbuf, const PerspCamera &cam) = 0;
		virtual void displayDepthMap(const DepthMap &depthMap, const Camera &cam) = 0;
		virtual void displayDepthMap(const std::array<std::shared_ptr<Engine::DepthMap>, CSM_NUM> &array_depthMap, DirLight *light) = 0;
		virtual void displayDepthMap(const DepthMap &depthMap, SpotLight *light) = 0;
	};
}


#endif
