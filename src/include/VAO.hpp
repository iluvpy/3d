#pragma once

#include <GL/glew.h>

class VAO {
public:
    void init();
    void bind();
    void unbind();

private:
    GLuint m_vao;
};