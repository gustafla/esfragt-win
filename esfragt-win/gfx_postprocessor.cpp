#include "gfx_postprocessor.h"
#include "util.h"
#include "text.h"
#include <string>
#include <iostream>

GfxPostProcessor::GfxPostProcessor(unsigned int w, unsigned int h, std::string fs) {
    //Load, compile, enable shaders
    std::string* fsTemp = new std::string;
    if (!loadFile(fs, *fsTemp)) {
        char e;
        std::cin >> e;
        exit(40);
    }
    if(shaderProgram.compProgram(SIMPLE_VS, *fsTemp) == GL_FALSE) {
        char e;
        std::cin >> e;
        exit(1);
    }
    delete fsTemp;
    glUseProgram(shaderProgram.getHandle());
    
    GLfloat res[2] = {
        w,
        h
    };

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);

    check();

    iChannel0 = new GfxTexture2D(NULL, res[0], res[1], 0, GL_RGBA, GL_NEAREST, GL_REPEAT);
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, iChannel0->getHandle(), 0);
    
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, res[0], res[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    //Here's our screen rectangle
    vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -1.0f;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = -1.0f;
}

GfxPostProcessor::~GfxPostProcessor() {
    delete iChannel0;
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}

void GfxPostProcessor::draw() {
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    iChannel0->bindToUnit(0);
    //Update time
    glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), glfwGetTime());

    //YOU NEED TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("v"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("v"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GfxPostProcessor::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}
