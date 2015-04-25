#ifndef GFX_POSTPROCESSOR_H
#define GFX_POSTPROCESSOR_H

#include "gfx.h"
#include "gfx_shader.h"
#include "gfx_texture_2D.h"
#include <string>
#include <vector>

class GfxPostProcessor {
    public:
        GfxPostProcessor(unsigned int w, unsigned int h, std::string vs);
        ~GfxPostProcessor();
        void draw();
        void bindFramebuffer();
    private:
        GfxTexture2D* iChannel0;
        GfxShader shaderProgram;
        GLfloat vertices[8];
        GLuint frameBuffer;
        GLuint renderBuffer;
};

#endif
