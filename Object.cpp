#include <Engine/Object.hpp>

engine::Object::Object(void)
{
  unsigned i;
  _idVAO = 0;
  _idVBO[0] = 0;
  _idVBO[1] = 0;
  _idTexture = 0;
  for(i=0 ; i<4 ; i++)
    {
      _matAmbient[i]=1.0;
      _matDiffuse[i]=1.0;
      _matSpecular[i]=1.0;
    }
  _matShininess[0]=1.0;
  _context = NULL;
  _shadow = NULL;
}

engine::Object::~Object(void)
{
  if(glIsVertexArray(_idVAO))
    glDeleteVertexArrays(1, &_idVAO);
  if(glIsBuffer(_idVBO[0]))
    glDeleteBuffers(1, &_idVBO[0]);
  if(glIsBuffer(_idVBO[1]))
    glDeleteBuffers(1, &_idVBO[1]);
  if(glIsTexture(_idTexture))
    glDeleteTextures(1, &_idTexture);
}

void engine::Object::setGLcontext(GLcontext *context)
{
  _context = context;
}

void engine::Object::setShadowMap(ShadowMap *shadow)
{
  _shadow = shadow;
}

void engine::Object::setTexture(const GLuint &id)
{
  if(glIsTexture(_idTexture))
    glDeleteTextures(1, &_idTexture);
  _idTexture = id;
}

void engine::Object::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matAmbient[0] = x;
  _matAmbient[1] = y;
  _matAmbient[2] = z;
  _matAmbient[3] = w;
}

void engine::Object::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matDiffuse[0] = x;
  _matDiffuse[1] = y;
  _matDiffuse[2] = z;
  _matDiffuse[3] = w;
}

void engine::Object::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matSpecular[0] = x;
  _matSpecular[1] = y;
  _matSpecular[2] = z;
  _matSpecular[3] = w;
}

void engine::Object::setShininess(const GLfloat &x)
{
  _matShininess[0] = x;
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void engine::Object::load(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
			  const GLuint &sizeIndexArray, const GLuint *indexArray)
{
  _numElement = sizeIndexArray/sizeof(GLuint);
  
  // Vertex Array et Vertex Buffer Object
  if(glIsVertexArray(_idVAO))
    glDeleteVertexArrays(1, &_idVAO);
  glGenVertexArrays(1, &_idVAO);
  glBindVertexArray(_idVAO);
  
  if(glIsBuffer(_idVBO[0]))
    glDeleteBuffers(1, &_idVBO[0]);
  glGenBuffers(1, &_idVBO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, _idVBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeVertexArray, vertexArray, GL_STATIC_DRAW);
  
  if(glIsBuffer(_idVBO[1]))
    glDeleteBuffers(1, &_idVBO[1]);
  glGenBuffers(1, &_idVBO[1]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idVBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexArray, indexArray, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(5*sizeof(GLfloat)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Object::display(void) const
{
  if(_context == NULL)
    {
      std::cerr << "You need to set the GLcontext before" << std::endl;
      return;
    }
  
  glUseProgram(_context->getProgramId());
  
  glBindVertexArray(_idVAO);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _idTexture);
  glUniform1i(_context->textureLocation, 0);
  if(_shadow != NULL)
    {
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());
      glUniform1i(_context->dirShadowMapLocation, 1);
    }
  
  glUniform4fv(_context->matAmbientLocation,  1, _matAmbient);
  glUniform4fv(_context->matDiffuseLocation,  1, _matDiffuse);
  glUniform4fv(_context->matSpecularLocation,  1, _matSpecular);
  glUniform1fv(_context->matShininessLocation, 1, _matShininess);

  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  if(_shadow != NULL)
    {
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  
  glBindVertexArray(0);
  
  glUseProgram(0);
}

void engine::Object::displayShadow(void) const
{  
  if(_shadow == NULL)
    {
      std::cerr << "You need to set the ShadowMap before" << std::endl;
      return;
    }
  
  glBindFramebuffer(GL_FRAMEBUFFER, _shadow->getIdFBO());
  
  glUseProgram(_shadow->getProgramId());
  
  glBindVertexArray(_idVAO);
  
  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
  glBindVertexArray(0);
  
  glUseProgram(0);
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
