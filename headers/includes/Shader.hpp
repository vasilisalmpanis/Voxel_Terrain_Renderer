#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <includes/Camera.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

class Shader
{
public:
    Shader(std::string vertexFileName, std::string fragmentFileName);
    Shader(const Shader &other);
    Shader &operator=(const Shader &other);
    ~Shader();

    unsigned int    getID(void) const;

    void            setBool(const std::string &name, bool value) const;
    void            setInt(const std::string &name, int value) const;
    void            setFloat(const std::string &name, float value) const;
    void            setMatrix4fv(const char *name, glm::mat4) const;

    void            use(void) const;
    void            del(void) const;

private:
    std::string     readFile(std::string fileName);
    GLuint          createShader(const char *shaderSource, GLenum shaderType);

    unsigned int m_ID;
};

#endif // SHADER_HPP
