#ifndef STATICMODEL_HEADER
#define STATICMODEL_HEADER

#include "../Model.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI StaticModel : public Model
		{
		public:
			StaticModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			StaticModel(const std::shared_ptr<StaticModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			~StaticModel(void);
			void loadFromFile(const GLchar *inFile);

			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) override;
			void displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) override;
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam) override;
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light) override;
			void displayDepthMaps(const std::vector<std::shared_ptr<DepthMap>> &depthMaps, const std::shared_ptr<DirLight> &light) override;
		};
	}
}

#endif