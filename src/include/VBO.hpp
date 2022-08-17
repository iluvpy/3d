#pragma once

#include <GL/glew.h>
#include <vector>
#include "Vertex.hpp"

class VBO {
public:
    void init(std::vector<Vertex> vertices);
    void bind();
    void unbind();
    void attrib();
    ~VBO();
private:
    GLuint m_vertexBuffer;
};