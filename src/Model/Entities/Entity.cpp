
#include "Entity.h"

Entity::Entity(LTexture* myTexture, int my_x_pos = 0, int my_y_pos = 0){

    this->entityTexture = myTexture;

    this->pos_x = my_x_pos;
    this->pos_y = my_y_pos;

    //Entity initialize itself without motion
    this->vel_x = 0;
    this->vel_y = 0;

    // Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de Entity", GetEnviroment(__FILE__, __FUNCTION__));
}


void Entity::update(int widthScreen, int heightScreen){

    //A priori the entity can be outside of the screen
    this->pos_x += vel_x;
    this->pos_y += vel_y;

    
}

void Entity::render(){

    this->entityTexture->render(this->pos_x, this->pos_y);

}