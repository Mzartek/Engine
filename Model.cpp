#include <Engine/Model.hpp>

engine::Model::Model(void)
{
  _index = 0;
  _program = NULL;
  _modelMatrixLocation = -1;
  _modelMatrix = glm::mat4(1.0);
}

engine::Model::~Model(void)
{
  unsigned i;
  for(i=0 ; i<_tObject.size(); i++)
    delete _tObject[i];
}

void engine::Model::setModelMatrixLocation(ShaderProgram *program, char const *name)
{
  _program = program;
  _modelMatrixLocation = glGetUniformLocation(_program->getId(), name);
}

unsigned engine::Model::createObject(GLfloat const *vertexArray, GLuint const &sizeVertexArray,
				     GLuint const *elementArray, GLuint const &sizeElementArray,
				     char const *pathTexture,
				     GLfloat const *ambiant, GLfloat const *diffuse, GLfloat const *specular, GLfloat const *shininess)
{
  unsigned id;
  Object *newone = new Object();
  
  engine::initBufferObject(GL_ARRAY_BUFFER, sizeVertexArray, &id, (void *)vertexArray);
  newone->setIdObject(id);
  engine::initBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeElementArray, &id, (void *)elementArray);
  newone->setIdElementObject(id, sizeElementArray/sizeof(GLuint));
  engine::loadTex(pathTexture, &id);
  newone->setIdTextureObject(id);
  newone->setAmbiant(ambiant[0], ambiant[1], ambiant[2], ambiant[3]);
  newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
  newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
  newone->setShininess(shininess[0]);
  
  _tObject.push_back(newone);
  return _index++;
}

void engine::Model::loadObj(char const *name)
{
  bool first = true;
  std::string str;
  std::ifstream fichier(name, std::ifstream::in | std::ifstream::binary);
  std::vector<GLfloat> v;
  std::vector<GLfloat> vn;
  std::vector<GLfloat> vt;
  std::vector<GLfloat> array;
  std::vector<GLuint> index;
  GLfloat tmp[3];
  GLulong num[3];
  GLuint trianglePoint, numIndex = 0;
  char *strTmp;
  
  GLfloat mat_ambiant[] = {0.2, 0.2, 0.2, 0.0};
  GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 0.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat mat_shininess[] = {2.0};
  
  if(fichier==NULL)
    {
      std::cerr << "Error while opening file: " << name << std::endl;
      return;
    }
  while(!fichier.eof())
    {
      fichier >> str;
      if(str[0]=='#')
	for(int i=fichier.get() ; i!='\n' ; i=fichier.get());
      else if(str == "mtllib")
	{
	  fichier >> str;
	  std::cout << "Il faut ouvrir le fichier: " << str << std::endl;
	}
      else if(str == "v")
	{
	  fichier >> tmp[0];
	  fichier >> tmp[1];
	  fichier >> tmp[2];
	  v.push_back(tmp[0]);
	  v.push_back(tmp[1]);
	  v.push_back(tmp[2]);
	}
      else if(str == "vn")
	{
	  fichier >> tmp[0];
	  fichier >> tmp[1];
	  fichier >> tmp[2];
	  vn.push_back(tmp[0]);
	  vn.push_back(tmp[1]);
	  vn.push_back(tmp[2]);
	}
      else if(str == "vt")
	{
	  fichier >> tmp[0];
	  fichier >> tmp[1];
	  vt.push_back(tmp[0]);
	  vt.push_back(tmp[1]);
	}
      else if(str == "f")
	{
	  while(1)
	    {
	      fichier >> str;
	      strTmp = &str[0];
	      num[0] = (strtoul(&strTmp[0], &strTmp, 0)-1) * 3;
	      num[1] = (strtoul(&strTmp[1], &strTmp, 0)-1) * 2;
	      num[2] = (strtoul(&strTmp[1], &strTmp, 0)-1) * 3;
	      array.push_back(v[num[0]]); array.push_back(v[num[0]+1]); array.push_back(v[num[0]+2]);
	      array.push_back(vt[num[1]]); array.push_back(vt[num[1]+1]);
	      array.push_back(vn[num[2]]); array.push_back(vn[num[2]+1]); array.push_back(vn[num[2]+2]);
	      if(fichier.get()=='\n')
		break;
	    }
	  trianglePoint = numIndex;
	  index.push_back(numIndex++);
	  index.push_back(numIndex++);
	  index.push_back(numIndex++);
	  for(; numIndex<(array.size()/8) ; numIndex++)
	    {
	      index.push_back(trianglePoint);
	      index.push_back(numIndex-1);
	      index.push_back(numIndex);
	    }
	}
      else if(str == "usemtl")
	{
	  if(first)
	    first = false;
	  else
	    {
	      createObject(&array[0], index.size()*sizeof(GLfloat),
	      		   &index[0], index.size()*sizeof(GLuint),
	      		   "resources/bleu.bmp",
	      		   mat_ambiant, mat_diffuse, mat_specular, mat_shininess);
	      std::cout << vt[vt.size()-2] << " " << vt[vt.size()-1] << std::endl;
	      numIndex=0;
	      array.clear();
	      index.clear();
	    }
	} 
    }
  createObject(&array[0], index.size()*sizeof(GLfloat),
  	       &index[0], index.size()*sizeof(GLuint),
  	       "resources/feu.jpg",
  	       mat_ambiant, mat_diffuse, mat_specular, mat_shininess);
}

void engine::Model::matIdentity(void)
{
  _modelMatrix = glm::mat4(1.0);
}

void engine::Model::matTranslate(GLfloat const &x, GLfloat const &y, GLfloat const &z)
{
  _modelMatrix = glm::translate(_modelMatrix, glm::vec3(x, y, z));
}

void engine::Model::matRotate(GLfloat const &angle, GLfloat const &x, GLfloat const &y, GLfloat const &z)
{
  _modelMatrix = glm::rotate(_modelMatrix, angle, glm::vec3(x, y, z));
}

void engine::Model::matScale(GLfloat const &x)
{
  _modelMatrix = glm::scale(_modelMatrix, glm::vec3(x));
}
  
void engine::Model::display(void)
{
  unsigned i;
  
  _program->use();
  glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
  
  for(i=0 ; i<_tObject.size(); i++)
    _tObject[i]->display();
}
