#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

class Shader {
public:
    void init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void bind();
    void unbind();
    GLint getUniformLocation(const std::string& name);
    ~Shader();

private:

    GLuint m_program; // 
    std::unordered_map<std::string, GLint> m_uLocations; // uniform locations
    void compileShader(GLuint shader, const char *shaderSrc);
    std::string readShader(const std::string& path);
};