#include <Engine/ShaderProgram.hpp>

GLbyte *engine::ShaderProgram::readText(const std::string filename)
{
	std::ifstream file(&filename[0], std::ifstream::in | std::ifstream::binary);
	GLbyte *content;
	GLuint size;

	if(!file.is_open())
	{
		std::cerr << "Error while opening file: " << filename << std::endl;
		exit(1);
	}
	//On obtient la taille du fichier
	file.seekg(0, std::ifstream::end);
	size = (GLuint)file.tellg();
	file.seekg(0, std::ifstream::beg);

	//On remplit content
	content = new GLbyte[size+1];
	assert(content != NULL);
	file.read((char *)content, size);
	content[size] = '\0';
  
	return content;
}

GLuint engine::ShaderProgram::loadShader(const std::string filename, GLenum type)
{
	GLuint id;
	GLbyte *content, *log;
	GLsizei logsize;
	GLint status;
  
	id = glCreateShader(type);
	if(id == 0)
	{
		std::cerr << "Error while creating shader" << std::endl;
		exit(1);
	}
  
	content = readText(filename);

	glShaderSource(id, 1, (const char **)&content, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);
        
		log = new GLbyte[logsize + 1];
		assert(log != NULL);

		log[logsize] = '\0';
        
		glGetShaderInfoLog(id, logsize, &logsize, (char *)log);
		std::cerr << "Error while compiling shader: " << filename << std::endl << log << std::endl;
        
		glDeleteShader(id);
		delete log;
		return 0;
	}
  
	delete content;
	return id;
}

engine::ShaderProgram::ShaderProgram(void)
{
	_idProgram = _idVertexShader = _idFragmentShader = 0;
}

engine::ShaderProgram::~ShaderProgram(void)
{
	if(glIsProgram(_idProgram))
		glDeleteProgram(_idProgram);
	if(glIsShader(_idVertexShader))
		glDeleteShader(_idVertexShader);
	if(glIsShader(_idFragmentShader))
		glDeleteShader(_idFragmentShader);
}

GLint engine::ShaderProgram::loadProgram(const std::string vs, const std::string fs)
{
	GLbyte *log;
	GLsizei logsize;
	GLint status;
  
	if(glIsProgram(_idProgram))
		glDeleteProgram(_idProgram);
	if(glIsShader(_idVertexShader))
		glDeleteShader(_idVertexShader);
	if(glIsShader(_idFragmentShader))
		glDeleteShader(_idFragmentShader);

	_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
	_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
  
	_idProgram = glCreateProgram();
	if(_idProgram == 0)
	{
		std::cerr << "Error while creating program" << std::endl;
		exit(1);
	}

	glAttachShader(_idProgram, _idVertexShader);
	glAttachShader(_idProgram, _idFragmentShader);
  
	glLinkProgram(_idProgram);
  
	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);
        
		log = new GLbyte[logsize + 1];
		assert(log != NULL);

		log[logsize] = '\0';
        
		glGetProgramInfoLog(_idProgram, logsize, &logsize, (char *)log);
		std::cerr << "Error while linking program: " << _idProgram << std::endl << log << std::endl;
        
		delete log;
		return 0;
	}

	return 1;
}

GLuint engine::ShaderProgram::getId(void)
{
	return _idProgram;
}
