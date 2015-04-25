#ifndef GFX_H
#define GFX_H

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void check();
void gfxBindFB0();

#endif