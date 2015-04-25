#include "gfx.h"
#include <iostream>
#include <cstdlib>

void check()
{
    static GLenum error;
    error = glGetError();

    if (error)
    {
        if (error == GL_OUT_OF_MEMORY)
            std::cout << "GPU OUT OF MEMORY! ;__;\n";
        if (error == GL_INVALID_OPERATION)
            std::cout << "Invalid GL operation. Fix your/my code.\n";
        exit(error);
    }
}

void gfxBindFB0() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}