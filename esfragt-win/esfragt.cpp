#include "esfragt.h"
#include <algorithm>
#include "text.h"
#include "config.h"
#include "tga_file.h"
#include "util.h"
#include <iostream>

Esfragt* Esfragt::instance = NULL;

Esfragt::Esfragt() {
    if (instance == NULL)
        instance = this;

    std::cout << "Compiling primary shader...\n";
    std::string fsTemp;
    if (Config::instance->prepend)
        fsTemp = UNIFORMS;
    if (!loadFile(Config::instance->fsName, fsTemp)) {
        char e;
        std::cin >> e;
        exit(40);
    }
    if(shaderProgram.compProgram(SIMPLE_VS, fsTemp) == GL_FALSE) {
        char e;
        std::cin >> e;
        exit(1);
    }

    shaderProgram.use();

    TGAFile* image;
    for (unsigned short i = 0; i < Config::instance->imgs; i++)
    {
        std::cout << "Image " << i << ": " << Config::instance->inames[i] << std::endl;
        image = new TGAFile;
        image->load(Config::instance->inames[i]);
        textures.push_back(new GfxTexture2D(image->getImage(), image->getWidth(), image->getHeight(), i, ((image->getBpp() == 32) ? GL_RGBA : GL_RGB)));
        delete image;
    }
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform1i(shaderProgram.getUfmHandle("iChannel1"), 1);
    glUniform1i(shaderProgram.getUfmHandle("iChannel2"), 2);
    glUniform1i(shaderProgram.getUfmHandle("iChannel3"), 3);
    glUniform1i(shaderProgram.getUfmHandle("iChannel4"), 4);
    glUniform1i(shaderProgram.getUfmHandle("iChannel5"), 5);
    glUniform1i(shaderProgram.getUfmHandle("iChannel6"), 6);
    glUniform1i(shaderProgram.getUfmHandle("iChannel7"), 7);
    check();

    glEnable(GL_BLEND);
    if (!Config::instance->devmode)
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
        glBlendFunc(GL_ONE, GL_SRC_ALPHA);

    check();

    GLfloat rect0[3*3*2] = {
        1.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
       -1.0f, -1.0f,  0.0f,

       -1.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
       -1.0f,  1.0f,  0.0f
    };
    std::copy(std::begin(rect0), std::end(rect0), std::begin(rectangle));

    GLfloat* res = new GLfloat[2];
    res[0] = Config::instance->w;
    res[1] = Config::instance->h;
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    delete res;

    pp = NULL;
    if (Config::instance->ppName != "") {
        std::cout << "Compiling post processor shader...\n";
        pp = new GfxPostProcessor(Config::instance->w, Config::instance->h, Config::instance->ppName);
    }

    //glReleaseShaderCompiler();
}

void Esfragt::draw() {
    check();
    
    shaderProgram.use();
    if (pp) {
        pp->bindFramebuffer();
        if (Config::instance->clearPp)
            glClear(GL_COLOR_BUFFER_BIT);
    }
    glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), glfwGetTime());

    for (int i=0; i<Config::instance->imgs; i++) {
        textures[i]->bindToOwnUnit();
    }
    
    glVertexAttribPointer(shaderProgram.getAtrHandle("v"), 3, GL_FLOAT, GL_FALSE, 0, rectangle);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("v"));

    glDrawArrays(GL_TRIANGLES, 0, 3*2);
    if (pp) {
        gfxBindFB0();
        pp->draw();
        glClear(GL_COLOR_BUFFER_BIT);
    }
}