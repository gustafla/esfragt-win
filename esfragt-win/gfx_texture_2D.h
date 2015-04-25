#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include "gfx.h"

class GfxTexture2D
{
    public:
        GfxTexture2D(const unsigned char* image, unsigned int w, unsigned int h, unsigned int bind=0, uint32_t format=GL_RGB, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);
        ~GfxTexture2D();
        GLuint getHandle();
        void image2D(unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB);
        void bindToUnit(unsigned int unit);
        void bindToOwnUnit();
    private:
        GLuint handle;
        GLuint bound;
        unsigned int binding;
};

//void gfxLoadTexture2D(const unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);

#endif
