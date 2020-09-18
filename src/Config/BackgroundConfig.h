#ifndef BACKGROUNDCONFIG_HEADER
#define BACKGROUNDCONFIG_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class BackgroundConfig{
    public:
        BackgroundConfig();
        ~BackgroundConfig();
        void setPath(std::string path);
        void setVelocitiy(int vel);
        std::string getPath();
        int getVelocity();
    private:
        std::string path;
        int velocity;


};

#endif