#pragma once

#include <GL/glew.h>

class EBO {
public:
    void init();
    void bind(uint32_t* indices);
    void unbind();
private:
    GLuint m_indexBuffer;
};