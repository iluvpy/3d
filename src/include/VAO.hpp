#pragma once

#include "glewInclude.hpp"

class VAO {
public:
    void init();
    void bind();
    void unbind();

private:
    GLuint m_vao;
};