#ifndef HELICOPTER_HEADER
#define HELICOPTER_HEADER

#include <Engine/Graphics/StaticModel.hpp>

using namespace Engine;

class Helicopter
{
private:
     std::shared_ptr<Graphics::ShaderProgram> _objectProgram;
     std::shared_ptr<Graphics::ShaderProgram> _depthMapProgram;
     std::shared_ptr<Graphics::StaticModel> _corpsModel;
     std::shared_ptr<Graphics::StaticModel> _rotorModel;

     glm::vec3 _rotorOffset;
     bool _isMount;

public:
     Helicopter(void);
     ~Helicopter(void);
     const std::shared_ptr<Graphics::StaticModel> &getCorpsModel(void) const;
     const std::shared_ptr<Graphics::StaticModel> &getRotorModel(void) const;

     void setMount(bool isMount);
     
     void setPosition(const glm::vec3 &position);
     void setScale(const glm::vec3 &scale);
     void setRotation(const glm::vec3 &rotation);
     void setRotation(const glm::vec3 &axis, GLfloat angle);
     
     void addPosition(const glm::vec3 &position);
     void addScale(const glm::vec3 &scale);
     void addRotation(const glm::vec3 &rotation);
     void addRotation(const glm::vec3 &axis, GLfloat angle);
};

#endif
