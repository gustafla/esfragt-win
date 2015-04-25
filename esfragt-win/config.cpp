#include "config.h"
#include "util.h"
#include "text.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

Config* Config::instance = NULL;

Config::Config(int argc, char* argv[]):
fsName("esfragt.frag"),
w(1280),
h(720),
stretch(1),
devmode(false),
prepend(false),
fpsCounter(false),
fullScreen(false),
clearPp(true),
ppName(""),
fpsIn(100),
imgs(0)
{
    if (instance == NULL)
        instance = this;

    /*YAY crappy parameter checking ^__^*/
    bool gotName = false, useAuto = false;
    for (int n=1; n<argc; n++)
    {
        if (!strcmp(argv[n], "-w"))
        {
            n++;
            checkValueParam(n, argc, argv);
            w = atoi(argv[n]);
        }
            else if (!strcmp(argv[n], "-h"))
            {
                n++;
                checkValueParam(n, argc, argv);
                h = atoi(argv[n]);
            }
                else if (!strcmp(argv[n], "-s"))
                {
                    n++;
                    checkValueParam(n, argc, argv);
                    w = h = atoi(argv[n]);
                }
                    else if (!strcmp(argv[n], "--help"))
                    {
                        std::cout << DOC;
                        exit(0);
                    }
                        else if (!strcmp(argv[n], "--version"))
                        {
                            std::cout << VERSION;
                            exit(0);
                        }
                            else if (!strcmp(argv[n], "-f"))
                            {
                                fpsCounter = true;
                                if ((n+1)!=argc)
                                {
                                    std::string tmp = argv[n+1];
                                    if (isdigits(tmp))
                                    {
                                        n++;
                                        fpsIn = atoi(argv[n]);
                                    }
                                }
                            }
                                else if (!strcmp(argv[n], "-d"))
                                {
                                    devmode = true;
                                }
                                    else if (!strcmp(argv[n], "-u"))
                                    {
                                        prepend = true;
                                    }
                                        else if (!strcmp(argv[n], "-c"))
                                        {
                                            n++;
                                            checkValueParamf(n, argc, argv);
                                            stretch = atof(argv[n]);
                                            if (stretch < 1)
                                            {
                                                std::cout << ARGERR;
                                                exit(4);
                                            }
                                        }
                                            else if (!strcmp(argv[n], "-i"))
                                            {
                                                if (imgs >= 8)
                                                {
                                                    std::cout << "Too many images\n" << ARGERR;
                                                    exit(6);
                                                }
                                                n++;
                                                if (n==argc)
                                                {
                                                    std::cout << ARGERR;
                                                    exit(20);
                                                }
                                                inames[imgs]=argv[n];
                                                imgs++;
                                            }
                                                else if (!strcmp(argv[n], "-a"))
                                                {
                                                    useAuto = true;
                                                }
                                                    else if (!strcmp(argv[n], "-p"))
                                                    {
                                                        n++;
                                                        if (n==argc)
                                                        {
                                                            std::cout << ARGERR;
                                                            exit(23);
                                                        }
                                                        ppName=argv[n];
                                                    }
                                                        else if (!strcmp(argv[n], "-m"))
                                                        {
                                                            clearPp = false;
                                                        }
                                                            else if (!strcmp(argv[n], "--fullscreen"))
                                                            {
                                                                fullScreen = true;
                                                            }
                                                                else if (!gotName)
                                                                {
                                                                    fsName = argv[n];
                                                                    gotName = true;
                                                                }
                                                                    else
                                                                    {
                                                                        std::cout << "Unexpected parameter " << argv[n] << std::endl;
                                                                        std::cout << ARGERR;
                                                                        exit(5);
                                                                    }
    }
    if (useAuto) {
        glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &w, &h);
    }

    h /= stretch;
    w /= stretch;
}
