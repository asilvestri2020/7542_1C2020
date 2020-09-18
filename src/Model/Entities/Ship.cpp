#include "Ship.h"

using namespace std;

Ship::Ship(LTexture* myTexture, int my_x_pos, int my_y_pos):
    Entity(myTexture,my_x_pos,my_y_pos){

}

void Ship::handleEvent(SDL_Event& e){

    //If you press a key and hold, the IF statement validate only the first cycle 
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vel_y -= SHIP_VEL; break;
            case SDLK_DOWN: vel_y += SHIP_VEL; break;
            case SDLK_LEFT: vel_x -= SHIP_VEL; break;
            case SDLK_RIGHT: vel_x += SHIP_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vel_y += SHIP_VEL; break;
            case SDLK_DOWN: vel_y -= SHIP_VEL; break;
            case SDLK_LEFT: vel_x += SHIP_VEL; break;
            case SDLK_RIGHT: vel_x -= SHIP_VEL; break;
        }
    }

}

void Ship::update(int widthScreen, int heightScreen){

    if(!vel_x and !vel_y)return;

    //A priori the entity can be outside of the screen
    pos_x += vel_x;
    pos_y += vel_y;

    this->notifyMovement();

    //TODO: ¿agregar al log cuando el jugador intenta salir de la pantalla?
    if(pos_x < 0 || pos_x > widthScreen - entityTexture->getWidth()) pos_x -= vel_x;
    if(pos_y < 0 || pos_y > heightScreen - entityTexture->getHeight()) pos_y -= vel_y;

}

void Ship::notifyMovement()
{   
    //Get enviroment and movement info
    std::string enviromet = this->GetEnviroment(__FILE__,__FUNCTION__);
    std::string message = string("Nave moviendose a ");

    if(vel_x > 0) message += "DERECHA-";
    else if (vel_x < 0) message += "IZQUIERDA-";

    if(vel_y > 0) message += "ABAJO";
    else if (vel_y < 0) message += "ARRIBA";
    else message.pop_back();                //remove last chararter ("-")
    
    message += " al punto ";
    message += "(" + to_string(pos_x) + "," + to_string(pos_y)+")";

    this->NotifyDebug(message, enviromet);
}

void Ship::setVelocity(int mov_x,int mov_y){
        
    if(mov_x == 0)vel_x = 0;
    else if( mov_x < 0)vel_x = -SHIP_VEL;
    else vel_x = SHIP_VEL;

    if(mov_y == 0)vel_y = 0;
    else if( mov_y < 0)vel_y = -SHIP_VEL;
    else mov_y = SHIP_VEL;
}