#include <Engine/SkyBox.hpp>

engine::SkyBox::SkyBox()
{
  _idTexture = 0;
  _idVAO = 0;
  _idVBO = 0;
  _idIBO = 0;
  _program = NULL;
}

engine::SkyBox::~SkyBox()
{
  if(glIsTexture(_idTexture))
    glDeleteTextures(1, &_idTexture);
  if(glIsVertexArray(_idVAO))
    glDeleteVertexArrays(1, &_idVAO);
  if(glIsBuffer(_idVBO))
    glDeleteBuffers(1, &_idVBO);
  if(glIsBuffer(_idIBO))
    glDeleteBuffers(1, &_idIBO);
}

#define BUFFER_OFFSET(i) ((GLubyte *)NULL + (i))

void engine::SkyBox::load(std::string posx, std::string negx,
			  std::string posy, std::string negy,
			  std::string posz, std::string negz,
			  GLfloat dim, Camera *cam, ShaderProgram *program)
{
  GLuint i;
  GLenum cube_map_target[] = {   
    GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };
  SDL_Surface *image[6];
  image[0] = IMG_Load(&posx[0]);
  image[1] = IMG_Load(&negx[0]);
  image[2] = IMG_Load(&posy[0]);
  image[3] = IMG_Load(&negy[0]);
  image[4] = IMG_Load(&posz[0]);
  image[5] = IMG_Load(&negz[0]);
  
  if(glIsTexture(_idTexture))
    glDeleteTextures(1, &_idTexture);
  glGenTextures(1, &_idTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);
  
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  for(i=0 ; i<6 ; i++)
    {
      if(image[i]==NULL)
	{
	  std::cerr << "Error while loading image" << std::endl;
	  exit(1);
	}
      switch(testFormat(image[i]->format->format))
	{
	case RGB:
	  glTexImage2D(cube_map_target[i], 0, GL_RGB, image[i]->w, image[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->pixels);
	  break;
	case BGR:
	  glTexImage2D(cube_map_target[i], 0, GL_RGB, image[i]->w, image[i]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image[i]->pixels);
	  break;
	case RGBA:
	  glTexImage2D(cube_map_target[i], 0, GL_RGBA, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]->pixels);
	  break;
	default:
	  std::cerr << "Format " << image[i]->format->format << " unknown" << std::endl;
	  break;
	}
      SDL_FreeSurface(image[i]);
    }
  
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  GLfloat vertexArray[] = {
    +dim, -dim, -dim,
    -dim, -dim, -dim,
    -dim, -dim, +dim,
    +dim, -dim, +dim,
    +dim, +dim, -dim,
    -dim, +dim, -dim,
    -dim, +dim, +dim,
    +dim, +dim, +dim
  };
  GLuint indexArray[] = {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    0, 1, 5, 0, 5, 4,
    3, 2, 6, 3, 6, 7,
    1, 2, 6, 1, 6, 5,
    0, 3, 7, 0, 7, 4
  };
  _numElement = sizeof(indexArray)/sizeof(GLuint);
  
  if(glIsVertexArray(_idVAO))
    glDeleteVertexArrays(1, &_idVAO);
  glGenVertexArrays(1, &_idVAO);
  glBindVertexArray(_idVAO);
  
  if(glIsBuffer(_idVBO))
    glDeleteBuffers(1, &_idVBO);
  glGenBuffers(1, &_idVBO);
  glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertexArray, vertexArray, GL_STATIC_DRAW);
  
  if(glIsBuffer(_idIBO))
    glDeleteBuffers(1, &_idIBO);
  glGenBuffers(1, &_idIBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indexArray, indexArray, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  _cam = cam;
  _program = program;
  _MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
  _textureLocation = glGetUniformLocation(_program->getId(), "cubeMap");
}

#undef BUFFER_OFFSET

void engine::SkyBox::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  _angle = angle;
  _x = x;
  _y = y;
  _z = z;
}

void engine::SkyBox::display(void)
{
  GLfloat pos[16];
  if(_program == NULL)
    {
      std::cerr << "You need to load a SkyBox before" << std::endl;
      return;
    }

  matrixLoadIdentity(pos);
  matrixTranslate(pos, _cam->getPositionCamera()->_x, _cam->getPositionCamera()->_y, _cam->getPositionCamera()->_z);
  matrixRotate(pos, _angle, _x, _y, _z);
  matrixMultiply(pos, _cam->getMatrix(), pos);
  
  glDepthMask(GL_FALSE);
  glUseProgram(_program->getId());
  
  glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, pos);
  
  glBindVertexArray(_idVAO);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);
  glUniform1i(_textureLocation, 0);

  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  
  glBindVertexArray(0);
  
  glUseProgram(0);
  glDepthMask(GL_TRUE);
}
