#include "gfx_shader.h"
#include <iostream>

GfxShader::GfxShader():
handle(0)
{

}

GLuint GfxShader::getHandle()
{
    return handle;
}

unsigned int GfxShader::getUfmHandle(std::string name)
{
    if (uniforms.find(name) == uniforms.end())
        uniforms[name] = glGetUniformLocation(handle, name.c_str());
    return uniforms[name];
}

unsigned int GfxShader::getAtrHandle(std::string name)
{
    if (attributes.find(name) == attributes.end())
        attributes[name] = glGetAttribLocation(handle, name.c_str());
    return attributes[name];
}

GLuint GfxShader::compShader(GLenum type, const char* src)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);

    if (shader == 0)
        return 0;

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            std::cout << "Error compiling shader:\n" << infoLog << std::endl;
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLint GfxShader::compProgram(std::string vsString, std::string fsString)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    vertexShader = compShader(GL_VERTEX_SHADER, vsString.c_str());
    fragmentShader = compShader(GL_FRAGMENT_SHADER, fsString.c_str());

    handle = glCreateProgram();

    if (handle == 0)
        return 0;

    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);

    glLinkProgram(handle);

    glGetProgramiv(handle, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv ( handle, GL_INFO_LOG_LENGTH, &infoLen );

        if ( infoLen > 1 )
        {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);

            glGetProgramInfoLog ( handle, infoLen, NULL, infoLog);
            std::cout << "Error linking program:\n" << infoLog << std::endl;

            free(infoLog);
        }
        glDeleteProgram(handle);
        return GL_FALSE;
    }

    return GL_TRUE;
}

void GfxShader::use() {
    glUseProgram(handle);
}