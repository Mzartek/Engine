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
		StaticModel(ShaderProgram *gProgram, ShaderProgram *smProgram);
		StaticModel(StaticModel *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
		~StaticModel(void);
		void loadFromFile(const GLchar *inFile);

		void display(const GBuffer &gbuf, const PerspCamera &cam);
		void displayTransparent(const GBuffer &gbuf, const PerspCamera &cam);
		void displayDepthMap(const DepthMap &depthMap, const Camera &cam);
		void displayDepthMap(const std::array<std::shared_ptr<Engine::DepthMap>, CSM_NUM> &array_depthMap, DirLight *light);
		void displayDepthMap(const DepthMap &depthMap, SpotLight *light);
	};
}

#endif