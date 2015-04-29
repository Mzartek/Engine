#ifndef STATICMODEL_HEADER
#define STATICMODEL_HEADER

#include "Model.hpp"

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
		void display(GBuffer *g, PerspCamera *cam);
		void displayTransparent(GBuffer *gbuf, PerspCamera *cam);
		void displayDepthMap(DepthMap *dmap, Camera *cam);
		void displayDepthMap(DepthMap *dmaps, DirLight *light);
		void displayDepthMap(DepthMap *dmap, SpotLight *light);
	};
}

#endif