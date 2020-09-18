#ifndef _ENTITY_H
#define _ENTITY_H

#include "../../Utils/LoggerSubject.h"
#include "../../Utils/LTexture.h"


//The idea is that an entity can be able to move trought the level
//and interact with other entities. Like ships, enemies, asteroids

class Entity: public LoggerSubject{

    protected:
        
        //Pointer to the texture
        LTexture* entityTexture;
        
        //Position and velocity parameters
        int pos_x, pos_y;
        int vel_x, vel_y;
        SDL_RendererFlip flip;

    public:

        Entity(LTexture* myTexture, int my_x_pos, int my_y_pos);

        //Movement logic 
        void update(int widthScreen, int heightScreen);

        //Call to the texture's render function
        void render();

};
#endif