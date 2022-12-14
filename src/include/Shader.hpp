#pragma once

#include "glewInclude.hpp"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    void init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void bind();
    void unbind();
    void setInt(const std::string& name, int i);
    void setMatf4(const std::string& name, glm::mat4 mat);
    GLint getUniformLocation(const std::string& name);
    ~Shader();

private:

    GLuint m_program; // 
    std::unordered_map<std::string, GLint> m_uLocations; // uniform locations
    void compileShader(GLuint shader, const char *shaderSrc);
    std::string readShader(const std::string& path);
};