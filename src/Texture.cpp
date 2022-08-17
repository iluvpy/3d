#include "Texture.hpp"


void Texture::createFrom(const std::string &texturePath) {
    glGenTextures(1, &m_texture);  
    bind();
    // set the texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(m_shouldFlip);
    
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        throw std::runtime_error("Error while trying to load texture");
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_displayFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    stbi_image_free(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture);  
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::setDisplayFormat(GLenum format) {
    m_displayFormat = format;
}

void Texture::setInternalFormat(GLenum internalFormat) {
    m_internalFormat = internalFormat;
}

void Texture::setShouldFlip(bool val) {
    m_shouldFlip = val;
}


