#include "VAO.hpp"

void VAO::init() {
    glGenVertexArrays(1, &m_vao);
}

void VAO::bind() {
    glBindVertexArray(m_vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}
