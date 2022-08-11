#include "EBO.hpp"

void EBO::init() {
    glGenBuffers(1, &m_indexBuffer);
}

void EBO::bind(uint32_t* indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
