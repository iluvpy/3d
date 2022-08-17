#pragma once

#include "glewInclude.hpp"
#include <string>
#include <stdexcept>
#include "stb_image/stb_image.h"

class Texture {
public:
    void createFrom(const std::string &texturePath);
    void bind();
    void unbind();
    void setDisplayFormat(GLenum format);
    void setInternalFormat(GLenum internalFormat);
    void setShouldFlip(bool val);
private:
    GLuint m_texture;
    GLenum m_displayFormat = GL_RGB;
    GLenum m_internalFormat = GL_RGB;
    bool m_shouldFlip = false;
};