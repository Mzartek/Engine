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
		void setBumpMap(Texture2D *map);
		void setNormalMap(Texture2D *map);
		void setDisplacementMap(Texture2D *map);
		void setLightMap(Texture2D *map);

		glm::vec3 getDiffuse(void) const;
		glm::vec3 getSpecular(void) const;
		glm::vec3 getAmbient(void) const;
		glm::vec3 getEmissive(void) const;
		GLfloat getShininess(void) const;
		GLfloat getOpacity(void) const;
		
		Texture2D *getDiffuseTexture(void) const;
		Texture2D *getSpecularTexture(void) const;
		Texture2D *getAmbientTexture(void) const;
		Texture2D *getEmissiveTexture(void) const;
		Texture2D *getShininessTexture(void) const;
		Texture2D *getOpacityTexture(void) const;
		Texture2D *getBumpMap(void) const;
		Texture2D *getNormalMap(void) const;
		Texture2D *getDisplacementMap(void) const;
		Texture2D *getLightMap(void) const;

		GLboolean hasDiffuseTexture(void) const;
		GLboolean hasSpecularTexture(void) const;
		GLboolean hasAmbientTexture(void) const;
		GLboolean hasEmissiveTexture(void) const;
		GLboolean hasShininessTexture(void) const;
		GLboolean hasOpacityTexture(void) const;
		GLboolean hasBumpMap(void) const;
		GLboolean hasNormalMap(void) const;
		GLboolean hasDisplacementMap(void) const;
		GLboolean hasLightMap(void) const;

		GLuint getMatBuffer(void) const;
		GLuint getStateBuffer(void) const;
	};
}

#endif