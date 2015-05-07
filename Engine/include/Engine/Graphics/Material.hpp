#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER

#include "../Object.hpp"

#include <Engine/Graphics/Texture2D.hpp>
#include <Engine/Graphics/Buffer.hpp>

namespace Engine
{
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

		std::shared_ptr<Buffer> _matBuffer;
		std::shared_ptr<Buffer> _stateBuffer;
		
		std::shared_ptr<Texture2D> _diffuseTexture;
		std::shared_ptr<Texture2D> _specularTexture;
		std::shared_ptr<Texture2D> _ambientTexture;
		std::shared_ptr<Texture2D> _emissiveTexture;
		std::shared_ptr<Texture2D> _shininessTexture;
		std::shared_ptr<Texture2D> _opacityTexture;
		std::shared_ptr<Texture2D> _bumpMap;
		std::shared_ptr<Texture2D> _normalMap;
		std::shared_ptr<Texture2D> _displacementMap;
		std::shared_ptr<Texture2D> _lightMap;

	public:
		Material(void);
		~Material(void);

		void setDiffuse(const std::shared_ptr<glm::vec3> &color);
		void setSpecular(const std::shared_ptr<glm::vec3> &color);
		void setAmbient(const std::shared_ptr<glm::vec3> &color);
		void setEmissive(const std::shared_ptr<glm::vec3> &color);
		void setShininess(GLfloat shininess);
		void setOpacity(GLfloat opacity);

		void setDiffuseTexture(const std::shared_ptr<Texture2D> &tex);
		void setSpecularTexture(const std::shared_ptr<Texture2D> &tex);
		void setAmbientTexture(const std::shared_ptr<Texture2D> &tex);
		void setEmissiveTexture(const std::shared_ptr<Texture2D> &tex);
		void setShininessTexture(const std::shared_ptr<Texture2D> &tex);
		void setOpacityTexture(const std::shared_ptr<Texture2D> &tex);
		void setBumpMap(const std::shared_ptr<Texture2D> &tex);
		void setNormalMap(const std::shared_ptr<Texture2D> &tex);
		void setDisplacementMap(const std::shared_ptr<Texture2D> &tex);
		void setLightMap(const std::shared_ptr<Texture2D> &tex);

		const std::shared_ptr<glm::vec3> &getDiffuse(void) const;
		const std::shared_ptr<glm::vec3> &getSpecular(void) const;
		const std::shared_ptr<glm::vec3> &getAmbient(void) const;
		const std::shared_ptr<glm::vec3> &getEmissive(void) const;
		GLfloat getShininess(void) const;
		GLfloat getOpacity(void) const;
		
		const std::shared_ptr<Texture2D> &getDiffuseTexture(void) const;
		const std::shared_ptr<Texture2D> &getSpecularTexture(void) const;
		const std::shared_ptr<Texture2D> &getAmbientTexture(void) const;
		const std::shared_ptr<Texture2D> &getEmissiveTexture(void) const;
		const std::shared_ptr<Texture2D> &getShininessTexture(void) const;
		const std::shared_ptr<Texture2D> &getOpacityTexture(void) const;
		const std::shared_ptr<Texture2D> &getBumpMap(void) const;
		const std::shared_ptr<Texture2D> &getNormalMap(void) const;
		const std::shared_ptr<Texture2D> &getDisplacementMap(void) const;
		const std::shared_ptr<Texture2D> &getLightMap(void) const;

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