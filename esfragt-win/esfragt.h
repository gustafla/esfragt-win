#ifndef ESFRAGT_H
#define ESFRAGT_H

#include "gfx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "gfx_texture_2D.h"
#include "gfx_postprocessor.h"
#include "gfx_shader.h"

class Esfragt {
    public:
        static Esfragt* instance;
        Esfragt();
        void draw();
    private:
        GfxShader shaderProgram;
        std::vector<GfxTexture2D*> textures;
        GLfloat rectangle[3*3*2];
        GfxPostProcessor* pp;
};

#endif