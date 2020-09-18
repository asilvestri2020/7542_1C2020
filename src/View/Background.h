
#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Utils/LTexture.h"
#include "../Config/BackgroundConfig.h"
#include "../Config/BackgroundConfig.h"
#include "../Parser/Parser.h"

#include <vector>

class Background{
    
	public:

        Background(SDL_Renderer* renderer);

        //Loads media
        bool loadMedia(std::vector<backgroundConfig_t> confs, int screenWidth,int screenHeight);

        //Frees media and shuts down SDL
        void close();
        
        void update();
        void render();

        ~Background(void);
   
        
    private:

        std::vector<LTexture*> bgTextures;

        int* scrollingOffsets;
        int* scrollingVelocity;
        int acumFondo1;
        SDL_Renderer* gRenderer;

    };
#endif