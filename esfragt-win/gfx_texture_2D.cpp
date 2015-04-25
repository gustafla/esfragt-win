#include "gfx_texture_2D.h"
#include <iostream>

GfxTexture2D::GfxTexture2D(const unsigned char* image, unsigned int w, unsigned int h, unsigned int bind, uint32_t format, uint32_t filter, uint32_t wrap) {
    glActiveTexture(GL_TEXTURE0+bind);
    binding = bind;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}

GfxTexture2D::~GfxTexture2D() {
    glDeleteTextures(1, &handle);
}

GLuint GfxTexture2D::getHandle()
{
    return handle;
}

void GfxTexture2D::bindToUnit(unsigned int unit) {
    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D, handle);
    bound = unit;
}

void GfxTexture2D::bindToOwnUnit() {
    bindToUnit(binding);
}

void GfxTexture2D::image2D(unsigned char* image, unsigned int w, unsigned int h, uint32_t format) {
    bindToUnit(0);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}

/*void gfxLoadTexture2D(const unsigned char* image, unsigned int w, unsigned int h, uint32_t format, uint32_t filter, uint32_t wrap)
{
    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}*/
