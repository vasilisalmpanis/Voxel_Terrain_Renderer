#include <includes/Shader.hpp>

Shader::Shader(std::string vertexFileName, std::string fragmentFileName) : m_ID(0)
{
	std::string vertexShaderSource = readFile(vertexFileName);
	std::string fragmentShaderSource = readFile(fragmentFileName);
	if (vertexShaderSource.empty() || fragmentShaderSource.empty())
	{
		std::cout << "Failed to read shader files" << std::endl;
		throw std::exception();
	}
	GLuint vertexShader = createShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const Shader &other) : m_ID(0)
{
    *this = other;
}

Shader &Shader::operator=(const Shader &other)
{
    if (this != &other)
        m_ID = other.m_ID;
    return (*this);
}

Shader::~Shader(void) {}

std::string Shader::readFile(std::string fileName)
{
	std::ifstream shaderFile;
	shaderFile.open(fileName);
	if (!shaderFile.is_open() && !shaderFile.good())
	{
		std::cout << "Failed to open file: " << fileName << std::endl;
		return "";
	}
	std::stringstream shaderCode;
	shaderCode << shaderFile.rdbuf();
	return shaderCode.str();
}

GLuint Shader::createShader(const char *shaderSource, GLenum shaderType)
{

	GLuint shader = glCreateShader(shaderType);
	// Attach the vertex shader source code to the vertex shader object
	glShaderSource(shader, 1, &shaderSource, NULL);
	// Compile the vertex shader into machine code
	glCompileShader(shader);
	int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << shaderType << std::endl;
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
	return (shader);
}


// Getters

unsigned int Shader::getID(void) const
{
    return m_ID;
}

// Setters
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}


// Public

void Shader::use(void) const 
{
    glUseProgram(m_ID);
}

void Shader::del(void) const
{
    glDeleteProgram(m_ID);
}