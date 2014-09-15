#include <Engine/ShaderProgram.hpp>

static GLchar *readText(const GLchar *filename)
{
	std::ifstream file(filename, std::ifstream::in | std::ifstream::binary);
	GLchar *content;
	GLint size;

	if(!file.is_open())
	{
		std::cerr << "Error while opening file: " << filename << std::endl;
		exit(1);
	}
	// Lenght of the file
	file.seekg(0, std::ifstream::end);
	size = (GLint)file.tellg();
	file.seekg(0, std::ifstream::beg);

	// Add content
	content = new GLchar[size + 1];
	file.read(content, size);
	content[size] = '\0';

	file.close();
	return content;
}

static GLuint loadShader(const GLchar *filename, const GLenum &type)
{
	GLuint id;
	GLchar *content, *log;
	GLsizei logsize;
	GLint status;

	id = glCreateShader(type);
	if(id == 0)
	{
		std::cerr << "Error while creating shader" << std::endl;
		exit(1);
	}

	content = readText(filename);

	glShaderSource(id, 1, (const GLchar **)&content, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetShaderInfoLog(id, logsize, &logsize, log);
		std::cerr << "Error while compiling shader: " << filename << std::endl << log << std::endl;

		glDeleteShader(id);
		delete[] log;
		exit(1);
	}

	delete[] content;
	return id;
}

engine::ShaderProgram::ShaderProgram(void)
{
	_idProgram = 0;
	_idVertexShader = 0;
	_idTessControlShader = 0;
	_idTessEvaluationShader = 0;
	_idGeometryShader = 0;
	_idFragmentShader = 0;
}

engine::ShaderProgram::~ShaderProgram(void)
{
	if(glIsProgram(_idProgram))
		glDeleteProgram(_idProgram);
	if(glIsShader(_idVertexShader))
		glDeleteShader(_idVertexShader);
	if (glIsShader(_idTessControlShader))
		glDeleteShader(_idTessControlShader);
	if (glIsShader(_idTessEvaluationShader))
		glDeleteShader(_idTessEvaluationShader);
	if (glIsShader(_idGeometryShader))
		glDeleteShader(_idGeometryShader);
	if(glIsShader(_idFragmentShader))
		glDeleteShader(_idFragmentShader);
}

void engine::ShaderProgram::loadProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs)
{
	GLchar *log;
	GLsizei logsize;
	GLint status;

	if (glIsProgram(_idProgram))
		glDeleteProgram(_idProgram);
	if (glIsShader(_idVertexShader))
		glDeleteShader(_idVertexShader);
	if (glIsShader(_idTessControlShader))
		glDeleteShader(_idTessControlShader);
	if (glIsShader(_idTessEvaluationShader))
		glDeleteShader(_idTessEvaluationShader);
	if (glIsShader(_idGeometryShader))
		glDeleteShader(_idGeometryShader);
	if (glIsShader(_idFragmentShader))
		glDeleteShader(_idFragmentShader);

	_idProgram = glCreateProgram();
	if (_idProgram == 0)
	{
		std::cerr << "Error while creating program" << std::endl;
		exit(1);
	}

	if (vs == NULL)
	{
		std::cerr << "Need a Vertex Shader for ShaderProgram" << std::endl;
		exit(1);
	}
	_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
	glAttachShader(_idProgram, _idVertexShader);

	if (tcs != NULL)
	{
		_idTessControlShader = loadShader(tcs, GL_TESS_CONTROL_SHADER);
		glAttachShader(_idProgram, _idTessControlShader);
	}

	if (tes != NULL)
	{
		_idTessEvaluationShader = loadShader(tes, GL_TESS_EVALUATION_SHADER);
		glAttachShader(_idProgram, _idTessEvaluationShader);
	}

	if (gs != NULL)
	{
		_idGeometryShader = loadShader(gs, GL_GEOMETRY_SHADER);
		glAttachShader(_idProgram, _idGeometryShader);
	}

	if (fs != NULL)
	{
		_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
		glAttachShader(_idProgram, _idFragmentShader);
	}

	glLinkProgram(_idProgram);

	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::cerr << "Error while linking program: " << _idProgram << std::endl << log << std::endl;

		delete[] log;
		exit(1);
	}
}

GLuint engine::ShaderProgram::getId(void)
{
	return _idProgram;
}
