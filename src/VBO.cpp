#include "VBO.hpp"

void VBO::init(std::vector<Vertex> vertices) {
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() {

}