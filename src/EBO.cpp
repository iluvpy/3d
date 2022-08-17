#include "EBO.hpp"

void EBO::init(std::vector<unsigned int> indices) {
    glGenBuffers(1, &m_indexBuffer);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW); 
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
