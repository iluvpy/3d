#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

class Shader {
public:
    void init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void bind();
    void unbind();
    ~Shader();

private:

    GLuint m_program;
    
    void compileShader(GLuint shader, const char *shaderSrc);
    std::string readShader(const std::string& path);
};