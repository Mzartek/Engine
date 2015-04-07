#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "Object.hpp"

namespace Engine
{
	class Texture2D;
	class Buffer;

	class DLLAPI Material : public Object
	{
	private:
		struct mat
		{
			glm::vec3 ALIGN(16) diffuse;
			glm::vec3 ALIGN(16) specular;
			glm::vec3 ALIGN(16) ambient;
			glm::vec3 ALIGN(16) emissive;
			GLfloat shininess;
			GLfloat ALIGN(16) opacity;
		} _mat;

		struct state
		{
			GLint ALIGN(16) hasDiffuseTexture;
			GLint hasSpecularTexture;
			GLint hasAmbientTexture;
			GLint hasEmissiveTexture;
			GLint ALIGN(16) hasShininessTexture;
			GLint hasOpacityTexture;
			GLint hasBumpMap;
			GLint hasNormalMap;
			GLint ALIGN(16) hasDisplacementMap;
			GLint hasLightMap;
		} _state;

		Buffer *_matBuffer;
		Buffer *_stateBuffer;
		
		Texture2D *_diffuseTexture;
		Texture2D *_specularTexture;
		Texture2D *_ambientTexture;
		Texture2D *_emissiveTexture;
		Texture2D *_shininessTexture;
		Texture2D *_opacityTexture;
		Texture2D *_bumpMap;
		Texture2D *_normalMap;
		Texture2D *_displacementMap;
		Texture2D *_lightMap;

	public:
		Material(void);
		~Material(void);

		void setDiffuse(const glm::vec3 &color);
		void setSpecular(const glm::vec3 &color);
		void setAmbient(const glm::vec3 &color);
		void setEmissive(const glm::vec3 &color);
		void setShininess(const GLfloat &shininess);
		void setOpacity(const GLfloat &opacity);

		void setDiffuseTexture(Texture2D *tex);
		void setSpecularTexture(Texture2D *tex);
		void setAmbientTexture(Texture2D *tex);
		void setEmissiveTexture(Texture2D *tex);
		void setShininessTexture(Texture2D *tex);
		void setOpacityTexture(Texture2D *tex);
		void setbumpMap(Texture2D *map);
		void setNormalMap(Texture2D *map);
		void setDisplacementMap(Texture2D *map);
		void setLightMap(Texture2D *map);

		GLboolean hasDiffuseTexture(void);
		GLboolean hasSpecularTexture(void);
		GLboolean hasAmbientTexture(void);
		GLboolean hasEmissiveTexture(void);
		GLboolean hasShininessTexture(void);
		GLboolean hasOpacityTexture(void);
		GLboolean hasBumpMap(void);
		GLboolean hasNormalMap(void);
		GLboolean hasDisplacementMap(void);
		GLboolean hasLightMap(void);
		
		Texture2D *getDiffuseTexture(void);
		Texture2D *getSpecularTexture(void);
		Texture2D *getAmbientTexture(void);
		Texture2D *getEmissiveTexture(void);
		Texture2D *getShininessTexture(void);
		Texture2D *getOpacityTexture(void);
		Texture2D *getBumpMap(void);
		Texture2D *getNormalMap(void);
		Texture2D *getDisplacementMap(void);
		Texture2D *getLightMap(void);

		GLuint getMatBuffer(void);
		GLuint getStateBuffer(void);
	};
}

#endif