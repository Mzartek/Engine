#ifndef OBJ_MODEL
#define OBJ_MODEL

#include "Model.hpp"

namespace engine
{
  class OBJModel : public Model
  {
  private:
    typedef struct material
    {
      std::string name;
      GLfloat ambiant[4];
      GLfloat diffuse[4];
      GLfloat specular[4];
      GLfloat shininess[1];
      std::string texture;
    } material;
    std::string findPath(const std::string name);
    GLuint getMaterial(const std::string name, const std::vector<material> mat);
    std::vector<material> loadMtl(const std::string path, const std::string name);
  public:
    void loadObj(const std::string name, GLubyte tex3D = 0);
  };
}

#endif
