#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "gfx.h"

class Config {
    public:
        static Config* instance;
        Config(int argc, char* argv[]);

        std::string fsName;
        std::string ppName;
        int w, h;
        float stretch;

        std::string inames[8];
        unsigned short imgs;

        bool devmode;
        bool prepend;
        bool fpsCounter;
        bool fullScreen;
        bool swInterval0;
        unsigned short fpsIn;
};

#endif
