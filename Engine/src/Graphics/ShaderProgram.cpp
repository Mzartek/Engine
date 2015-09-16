#include <Engine/Graphics/ShaderProgram.hpp>

#include <Engine/Tools/StringHandler.hpp>

inline GLuint loadShader(const GLchar *filename, const GLenum &type)
{
	GLuint id;
	GLchar *content, *log;
	GLsizei logsize;
	GLint status;

	id = glCreateShader(type);
	if (id == 0)
	{
		throw std::runtime_error("Error while creating shader");
	}

	content = Engine::Tools::readText(filename);

	glShaderSource(id, 1, const_cast<const GLchar **>(&content), nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetShaderInfoLog(id, logsize, &logsize, log);
		std::string errorMessage("Error while compiling shader: " + std::string(filename) + "\n" + log);

		glDeleteShader(id);
		delete[] log;

		throw std::runtime_error(errorMessage);
	}

	delete[] content;
	return id;
}

Engine::Graphics::ShaderProgram::ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs)
	: _idProgram(0), _idVertexShader(0), _idTessControlShader(0), _idTessEvaluationShader(0), _idGeometryShader(0), _idFragmentShader(0)
{
	GLchar *log;
	GLsizei logsize;
	GLint status;

	_idProgram = glCreateProgram();
	if (_idProgram == 0)
	{
		throw std::runtime_error("Error while creating program");
	}

	if (vs != nullptr)
	{
		_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
		glAttachShader(_idProgram, _idVertexShader);
	}

	if (tcs != nullptr)
	{
		_idTessControlShader = loadShader(tcs, GL_TESS_CONTROL_SHADER);
		glAttachShader(_idProgram, _idTessControlShader);
	}

	if (tes != nullptr)
	{
		_idTessEvaluationShader = loadShader(tes, GL_TESS_EVALUATION_SHADER);
		glAttachShader(_idProgram, _idTessEvaluationShader);
	}

	if (gs != nullptr)
	{
		_idGeometryShader = loadShader(gs, GL_GEOMETRY_SHADER);
		glAttachShader(_idProgram, _idGeometryShader);
	}

	if (fs != nullptr)
	{
		_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
		glAttachShader(_idProgram, _idFragmentShader);
	}

	glLinkProgram(_idProgram);

	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::string errorMessage("Error while linking program: " + std::to_string(_idProgram) + "\n" + log);

		delete[] log;

		throw std::runtime_error(errorMessage);
	}
}

Engine::Graphics::ShaderProgram::ShaderProgram(const GLchar *vs, const GLchar *tcs, const GLchar *tes, const GLchar *gs, const GLchar *fs, const GLchar **varyings, GLsizei count)
	: _idProgram(0), _idVertexShader(0), _idTessControlShader(0), _idTessEvaluationShader(0), _idGeometryShader(0), _idFragmentShader(0)
{
	GLchar *log;
	GLsizei logsize;
	GLint status;

	_idProgram = glCreateProgram();
	if (_idProgram == 0)
	{
		throw std::runtime_error("Error while creating program");
	}

	if (vs != nullptr)
	{
		_idVertexShader = loadShader(vs, GL_VERTEX_SHADER);
		glAttachShader(_idProgram, _idVertexShader);
	}

	if (tcs != nullptr)
	{
		_idTessControlShader = loadShader(tcs, GL_TESS_CONTROL_SHADER);
		glAttachShader(_idProgram, _idTessControlShader);
	}

	if (tes != nullptr)
	{
		_idTessEvaluationShader = loadShader(tes, GL_TESS_EVALUATION_SHADER);
		glAttachShader(_idProgram, _idTessEvaluationShader);
	}

	if (gs != nullptr)
	{
		_idGeometryShader = loadShader(gs, GL_GEOMETRY_SHADER);
		glAttachShader(_idProgram, _idGeometryShader);
	}

	if (fs != nullptr)
	{
		_idFragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
		glAttachShader(_idProgram, _idFragmentShader);
	}

	glTransformFeedbackVaryings(_idProgram, count, varyings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(_idProgram);

	glGetProgramiv(_idProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);

		log = new GLchar[logsize + 1];
		log[logsize] = '\0';

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::string errorMessage("Error while linking program: " + std::to_string(_idProgram) + "\n" + log);

		delete[] log;

		throw std::runtime_error(errorMessage);
	}
}

Engine::Graphics::ShaderProgram::~ShaderProgram(void)
{
	if (glIsProgram(_idProgram)) glDeleteProgram(_idProgram);
	if (glIsShader(_idVertexShader)) glDeleteShader(_idVertexShader);
	if (glIsShader(_idTessControlShader)) glDeleteShader(_idTessControlShader);
	if (glIsShader(_idTessEvaluationShader)) glDeleteShader(_idTessEvaluationShader);
	if (glIsShader(_idGeometryShader)) glDeleteShader(_idGeometryShader);
	if (glIsShader(_idFragmentShader)) glDeleteShader(_idFragmentShader);
}

GLuint Engine::Graphics::ShaderProgram::getId(void) const
{
	return _idProgram;
}
