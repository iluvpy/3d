#pragma once

#include "glewInclude.hpp"
#include <vector>

class EBO {
public:
    void init(std::vector<unsigned int> indices);
    void bind();
    void unbind();
private:
    GLuint m_indexBuffer;
};