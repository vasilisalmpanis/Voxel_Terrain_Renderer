#ifndef SHADER_HPP
# define SHADER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
	unsigned int        _ID;
	std::string			readFile(std::string fileName);
	GLuint				createShader(const char *shaderSource, GLenum shaderType);
	public:
		Shader(std::string vertexShader, std::string fragmentShader);
		Shader(const Shader &other);
		Shader &operator=(const Shader &other);
		~Shader();

		// Getters
		unsigned int    getID(void) const;

		// Setters (our setters are const because they dont modify our object)
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;

		// Public
		void			use(void) const;
		void			del(void) const;
		

};

#endif