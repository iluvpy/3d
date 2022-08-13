#pragma once

#include <GL/glew.h>
#include <vector>

class EBO {
public:
    void init();
    void bind(std::vector<unsigned int> indices);
    void unbind();
private:
    GLuint m_indexBuffer;
};