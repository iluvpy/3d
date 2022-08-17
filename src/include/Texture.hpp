#pragma once

#include <GL/glew.h>
#include <string>
#include <stdexcept>
#include "stb_image/stb_image.h"

class Texture {
public:
    void init(const std::string &texturePath);
    void bind();
    void unbind();

private:
    GLuint m_texture;
};