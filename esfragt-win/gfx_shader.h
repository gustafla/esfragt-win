#ifndef GFX_SHADER_H
#define GFX_SHADER_H

#include <map>
#include <string>
#include "gfx.h"

class GfxShader {
    public:
        GfxShader();
        GLuint getHandle();
        unsigned int getUfmHandle(std::string);
        unsigned int getAtrHandle(std::string);
        GLint compProgram(std::string vsString, std::string fsString);
        void use();
    private:
        std::map<std::string, unsigned int> uniforms;
        std::map<std::string, unsigned int> attributes;
    
        GLuint compShader(GLenum type, const char* src);
    
        GLuint handle;
};

#endif
