#include "VBO.hpp"

void VBO::init(std::vector<Vertex> vertices) {
    glGenBuffers(1, &m_vertexBuffer);
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
}


void VBO::attrib() {
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // text coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO() {

}