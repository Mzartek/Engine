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
		std::shared_ptr<glm::vec3> _position;
		std::shared_ptr<glm::vec3> _scale;
		std::shared_ptr<glm::quat> _rotation;

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

		std::shared_ptr<std::vector<std::shared_ptr<Mesh>>> _tMesh;

		std::shared_ptr<Buffer> _matrixBuffer;
		std::shared_ptr<Buffer> _cameraBuffer;

		std::shared_ptr<glm::mat4> _modelMatrix;
		std::shared_ptr<glm::mat4> _normalMatrix;

		std::shared_ptr<TextureCube> _cubeTexture;

		std::shared_ptr<ShaderProgram> _gProgram;
		std::shared_ptr<ShaderProgram> _smProgram;

		void checkMatrix(void);

	public:
		Model(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
		Model(const std::shared_ptr<Model> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
		~Model(void);

		void addMesh(const std::shared_ptr<Mesh> &mesh);
		void sortMesh(void);
		void setPosition(const std::shared_ptr<glm::vec3> &position);
		void setScale(const std::shared_ptr<glm::vec3> &scale);
		void setRotation(const std::shared_ptr<glm::vec3> &rotation);
		void setRotation(const std::shared_ptr<glm::vec3> &axis, GLfloat angle);
		void setCubeTexture(const std::shared_ptr<TextureCube> &cubeTexture);
		const std::shared_ptr<glm::vec3> &getPosition(void) const;
		const std::shared_ptr<glm::vec3> &getScale(void) const;
		std::pair<const std::shared_ptr<glm::vec3> &, GLfloat> getAxisAngleRotation(void) const;
		const std::shared_ptr<Mesh> &getMesh(GLuint num) const;

		virtual void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) = 0;
		virtual void displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) = 0;
		virtual void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam) = 0;
		virtual void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light) = 0;
		virtual void displayDepthMaps(const std::shared_ptr<DepthMap> &depthMap0, const std::shared_ptr<DepthMap> &depthMap1, const std::shared_ptr<DepthMap> &depthMap2, 
			const std::shared_ptr<DirLight> &light) = 0;
	};
}


#endif
