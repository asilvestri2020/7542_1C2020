#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../Utils/LoggerSubject.h"
class Window: public LoggerSubject {

    public:

        //Init() returns true only if SDL, WINDOW, RENDERER and SDL_IMAGE 
        //initialized correctly
        bool init(int aWidth, int aHeight);

        //Close SDL and subsystems
        void close();

        //Screen management
        void clearScreen();
        void renderScreen();

        SDL_Renderer* getRenderer();

        int getWidth();
        int getHeight();


    private:

        //Screen dimension
        int height,width;
        
        SDL_Window* window;
        SDL_Renderer* renderer;

};


#endif