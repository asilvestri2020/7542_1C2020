#ifndef SHIP_HEADER
#define SHIP_HEADER

#include <stdio.h>
#include <string.h>
#include "Entity.h"

using namespace std;

class Ship: public Entity{

    //Mas adelante deberia ser una variable actualizable por el jugador
	static const int SHIP_VEL = 5;

    public:
    
        Ship(LTexture* myTexture, int my_x_pos= 0, int my_y_pos= 0);
        void handleEvent( SDL_Event& e);
        void update(int widthScreen, int heightScreen);
        void setVelocity(int mov_x, int mov_y);

    private:

        void notifyMovement();
};

#endif