#include "EBO.hpp"

void EBO::init() {
    glGenBuffers(1, &m_indexBuffer);
}

void EBO::bind(std::vector<unsigned int> indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW); 
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
