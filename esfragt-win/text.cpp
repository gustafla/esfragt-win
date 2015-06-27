#include "text.h"
#include <string>

const std::string UNIFORMS = "uniform vec2 iResolution; "
                             "uniform float iGlobalTime; "
                             "uniform sampler2D iChannel0; "
                             "uniform sampler2D iChannel1; "
                             "uniform sampler2D iChannel2; "
                             "uniform sampler2D iChannel3; "
                             "uniform sampler2D iChannel4; "
                             "uniform sampler2D iChannel5; "
                             "uniform sampler2D iChannel6; "
                             "uniform sampler2D iChannel7; ";

const std::string VERSION = "GL ES Fragment Shader Thingy for Windows - esfragt4win 1.0.1\n";

const std::string ARGERR = "Go fix your parameters.\n"
                           "Try 'esfragt --help' for more information.\n";

const std::string DOC = "Usage: esfragt [OPTION]... FILE\n"
                        "Load and run a GLSL fragment shader source.\n"
                        "\n"
                        "  -a                set window size to display size (automatic resolution)\n"
                        "  -w                window width\n"
                        "  -h                window height\n"
                        "  -s                window width and height, a square\n"
                        "  -c                divide backbuffer size by n, prone to rounding error\n"
                        "  -f                print out a FPS reading after every n frame(s)\n"
                        "                    (default 100)\n"
						"      --nf          do not print FPS readings\n"
                        "  -v                set swap interval to 0. Removes fps limit and disables \"vsync\"?\n"
                        "  -u                prepend all uniforms to FILE\n"
                        "                    (first line can't be a preprocessor instruction,\n"
                        "                    recommended leaving it empty)\n"
                        "  -i                specify an image file, only TGA supported\n"
                        "                    order of parameter decides iChannelX number\n"
                        "  -p                also run a post processing shader file.\n"
                        "                    \"iChannel0\" is frame input.\n"
                        "      --help        display this help and exit\n"
                        "      --version     display version information and exit\n"
                        "\n"
                        "With no FILE, try esfragt.frag\n"
                        "\n"
                        "Your shader will be running on two triangles\n"
                        "with a minimal vertex shader, filling the window.\n\n"
                        "Available uniforms:\n"
                        "\n"
                        "uniform vec2 iResolution        window resolution\n"
                        "uniform float iGlobalTime       time in seconds since program start\n"
                        "uniform sampler2D iChannel0-7   optional input data (images for now)\n"
                        "\n"
                        "You can report bugs or send mail/spam/\"offers\" to luutifa@gmail.com\n"
                        "esfragt home page: <http://luutifa.tk/esfragt/>\n";

const std::string SIMPLE_VS = "attribute vec4 v;\nvoid main(){gl_Position=v;}\n";
