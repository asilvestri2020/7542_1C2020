#ifndef _SCENE_HEADER
#define _SCENE_HEADER

#include "SDL2/SDL.h"
#include <string>
#include <stdio.h>

class Scene{

    public:
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void eventHandler(SDL_Event& e ) = 0;
        virtual bool loadSceneResources() = 0;

        virtual void startScene();
        virtual void finishScene();
};

#endif