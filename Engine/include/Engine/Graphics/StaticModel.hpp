#ifndef STATICMODEL_HEADER
#define STATICMODEL_HEADER

#include "Model.hpp"
#include "StaticMesh.hpp"

namespace Engine
{
	class DLLAPI StaticModel : public Model
	{
	private:
		struct
		{
			glm::mat4 MVP;
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 model;
			glm::mat4 normal;
		} _matrix;

	public:
		StaticModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
		StaticModel(const std::shared_ptr<StaticModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
		~StaticModel(void);
		void loadFromFile(const GLchar *inFile);

		void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam);
		void displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam);
		void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam);
		void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light);
		void displayDepthMaps(const std::shared_ptr<DepthMap> &depthMap0, const std::shared_ptr<DepthMap> &depthMap1, const std::shared_ptr<DepthMap> &depthMap2,
			const std::shared_ptr<DirLight> &light);
	};
}

#endif