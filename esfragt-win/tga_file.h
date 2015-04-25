#ifndef TGA_FILE_H
#define TGA_FILE_H

#include <fstream>
#include <string>

class TGAFile {
    public:
        bool load(std::string filename);
        unsigned int getWidth();
        unsigned int getHeight();
        unsigned int getBpp(); //bits per pixel
        unsigned char* getImage();
    
        ~TGAFile();
    protected:
        void errorPrint(std::string);
        bool loadUncompressed();
        bool loadCompressed();
        bool loadHeader();
        std::ifstream file;
        unsigned char header[6];
        unsigned char* imageData;
        unsigned int imageSize;
        unsigned int bpp;
        unsigned int width;
        unsigned int height;
};

#endif
