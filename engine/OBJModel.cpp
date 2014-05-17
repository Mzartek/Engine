#include <Engine/OBJModel.hpp>

std::string engine::OBJModel::findPath(const std::string name)
{
  GLuint size, i;
  std::string path;

  for(size=i=0 ; name[i]!='\0' ; i++)
    if(name[i]=='/')
      size=i+1;

  path.insert(0, name, 0, size);

  return path;
}

GLuint engine::OBJModel::getMaterial(const std::string name, const std::vector<material> mat)
{
  GLuint i;
  for(i=0 ; i<mat.size(); i++)
    if(name == mat[i].name)
      return i;
  std::cerr << "Unable du found material: " << name << std::endl;
  exit(1);
  return 0;
}

std::vector<engine::OBJModel::material> engine::OBJModel::loadMtl(const std::string path, const std::string name)
{
  std::ifstream mtlfile;
  std::string str;
  std::vector<material> mat;
  material tmp;
  GLfloat num;
  GLboolean first = true;
  GLint i;

  tmp.ambiant[0]=0.2f; tmp.ambiant[1]=0.2f; tmp.ambiant[2]=0.2f; tmp.ambiant[3]=1.0f;
  tmp.diffuse[0]=0.8f; tmp.diffuse[1]=0.8f; tmp.diffuse[2]=0.8f; tmp.diffuse[3]=1.0f;
  tmp.specular[0]=1.0f; tmp.specular[1]=1.0f; tmp.specular[2]=1.0f; tmp.specular[3]=1.0f;
  tmp.shininess[0]=0.0f;
  tmp.texture = path + "none.png";
  mtlfile.open(&(path + name)[0], std::ifstream::in | std::ifstream::binary);
  if(!mtlfile.is_open())
    {
      std::cerr << "Fail to open: " << name << std::endl;
      exit(1);
    }
  while(!mtlfile.eof())
    {
      mtlfile >> str;
      if(str[0]=='#')
	for(i=mtlfile.get() ; i!='\n' ; i=mtlfile.get());
      if(str == "Kd")
	{
	  mtlfile >> num;
	  tmp.diffuse[0] = num;
	  mtlfile >> num;
	  tmp.diffuse[1] = num;
	  mtlfile >> num;
	  tmp.diffuse[2] = num;
	}
      else if(str == "Ka")
	{
	  mtlfile >> num;
	  tmp.ambiant[0] = num;
	  mtlfile >> num;
	  tmp.ambiant[1] = num;
	  mtlfile >> num;
	  tmp.ambiant[2] = num;
	}
      else if(str == "Ks")
	{
	  mtlfile >> num;
	  tmp.specular[0] = num;
	  mtlfile >> num;
	  tmp.specular[1] = num;
	  mtlfile >> num;
	  tmp.specular[2] = num;
	}
      else if(str == "Ns")
	{
	  mtlfile >> num;
	  tmp.shininess[0] = num;
	}
      else if(str == "d")
	{
	  mtlfile >> num;
	  tmp.diffuse[3] = num;
	  tmp.ambiant[3] = num;
	  tmp.specular[3] = num;
	}
      else if(str == "map_Kd")
	{
	  mtlfile >> str;
	  tmp.texture = path + str;
	}
      else if(str == "newmtl")
	{
	  mtlfile >> str;
	  if(first)
	    {
	      first = false;
	      tmp.name = str;
	    }
	  else
	    {
	      mat.push_back(tmp);
	      tmp.name = str;
	      tmp.ambiant[0]=0.2f; tmp.ambiant[1]=0.2f; tmp.ambiant[2]=0.2f; tmp.ambiant[3]=1.0f;
	      tmp.diffuse[0]=0.8f; tmp.diffuse[1]=0.8f; tmp.diffuse[2]=0.8f; tmp.diffuse[3]=1.0f;
	      tmp.specular[0]=1.0f; tmp.specular[1]=1.0f; tmp.specular[2]=1.0f; tmp.specular[3]=1.0f;
	      tmp.shininess[0]=0.0f;
	      tmp.texture = path + "none.png";
	    }
	}
    }
  mat.push_back(tmp);
  return mat;
}

void engine::OBJModel::loadObj(const std::string name, GLenum texType)
{
  std::ifstream objfile(&name[0], std::ifstream::in | std::ifstream::binary);
  std::string str;
  std::vector<GLfloat> v;
  std::vector<GLfloat> vn;
  std::vector<GLfloat> vt;
  GLfloat tmp[3];
  GLint i, num[3];
  GLuint savePoint, matindex = 0, numIndex = 0;
  GLchar *strtmp;
  GLboolean first = true, takestr = true;
  
  std::vector<GLfloat> array;
  std::vector<GLuint> index;
  std::vector<material> mat;
  
  if(!objfile.is_open())
    {
      std::cerr << "Error while opening file: " << name << std::endl;
      return;
    }
  
  while(objfile.good())
    {
      if(takestr)
	objfile >> str;
      else
	takestr = true;
      if(str[0]=='#')
	for(i=objfile.get() ; i!='\n' && objfile.good() ; i=objfile.get());
      else if(str == "mtllib")
	{
	  objfile >> str;
	  mat = loadMtl(findPath(name), &str[0]);
	}      
      else if(str == "v")
	{
	  objfile >> tmp[0];
	  objfile >> tmp[1];
	  objfile >> tmp[2];
	  v.push_back(tmp[0]);
	  v.push_back(tmp[1]);
	  v.push_back(tmp[2]);
	}      
      else if(str == "vn")
	{
	  objfile >> tmp[0];
	  objfile >> tmp[1];
	  objfile >> tmp[2];
	  vn.push_back(tmp[0]);
	  vn.push_back(tmp[1]);
	  vn.push_back(tmp[2]);
	}      
      else if(str == "vt")
	{
	  objfile >> tmp[0];
	  objfile >> tmp[1];
	  vt.push_back(tmp[0]);
	  vt.push_back(tmp[1]);
	  if(texType == GL_TEXTURE_3D)
	    objfile >> tmp[0];
	}      
      else if(str == "f")
	{
	  for(objfile >> str ; (isdigit(str[0]) || str[0]=='-') && objfile.good() ; objfile >> str)
	    {
	      strtmp = &str[0];

	      num[0] = (GLint)strtol(&strtmp[0], &strtmp, 0);
	      num[1] = (GLint)strtol(&strtmp[1], &strtmp, 0);
	      num[2] = (GLint)strtol(&strtmp[1], &strtmp, 0);

	      if(num[0]>0)
		{
		  num[0] = (num[0]-1) * 3;
		  num[1] = (num[1]-1) * 2;
		  num[2] = (num[2]-1) * 3;
		}
	      else
		{
		  num[0] = (GLint)v.size() + (num[0] * 3);
		  num[1] = (GLint)vt.size() + (num[1] * 2);
		  num[2] = (GLint)vn.size() + (num[2] * 3);
		}

	      array.push_back(v[num[0]]); array.push_back(v[num[0]+1]); array.push_back(v[num[0]+2]);
	      array.push_back(vt[num[1]]); array.push_back(vt[num[1]+1]);
	      array.push_back(vn[num[2]]); array.push_back(vn[num[2]+1]); array.push_back(vn[num[2]+2]);
	    }
	  savePoint = numIndex;
	  index.push_back(numIndex++);
	  index.push_back(numIndex++);
	  index.push_back(numIndex++);
	  while(numIndex<(array.size()/8))
	    {
	      index.push_back(savePoint);
	      index.push_back(numIndex-1);
	      index.push_back(numIndex++);
	    }
	  takestr=false;
	}      
      else if(str == "usemtl")
	{
	  objfile >> str;
	  if(first)
	    {
	      first = false;
	      matindex = getMaterial(str, mat);
	    }
	  else
	    {
	      createObject((GLsizei)array.size()*(GLsizei)sizeof(GLfloat), &array[0],
			   (GLsizei)index.size()*(GLsizei)sizeof(GLuint), &index[0],
	      		   mat[matindex].texture,
	      		   mat[matindex].ambiant, mat[matindex].diffuse, mat[matindex].specular, mat[matindex].shininess);
	      numIndex=0;
	      array.clear();
	      index.clear();
	      matindex = getMaterial(str, mat);
	    }
	} 
    }
  createObject((GLsizei)array.size()*(GLsizei)sizeof(GLfloat), &array[0],
	       (GLsizei)index.size()*(GLsizei)sizeof(GLuint), &index[0],
	       mat[matindex].texture,
	       mat[matindex].ambiant, mat[matindex].diffuse, mat[matindex].specular, mat[matindex].shininess);
}
