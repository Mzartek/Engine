#ifndef HELICOPTER_HEADER
#define HELICOPTER_HEADER

#include <Engine/Graphics/StaticModel.hpp>

class Helicopter
{
private:
     std::shared_ptr<Engine::ShaderProgram> _objectProgram;
     std::shared_ptr<Engine::ShaderProgram> _depthMapProgram;
     std::shared_ptr<Engine::StaticModel> _corpsModel;
     std::shared_ptr<Engine::StaticModel> _rotorModel;

     glm::vec3 _rotorOffset;
     bool _isMount;

public:
     Helicopter(void);
     ~Helicopter(void);
     const std::shared_ptr<Engine::StaticModel> &getCorpsModel(void) const;
     const std::shared_ptr<Engine::StaticModel> &getRotorModel(void) const;

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
