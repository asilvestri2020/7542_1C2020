#include "Enemy.h"

//Player* Enemy::sPlayer = nullptr;


Enemy::Enemy(int spawnpos_x, int spawnpos_y, int vel_x, int vel_y, LTexture* texture):Entity(texture, spawnpos_x, spawnpos_y){


	this->vel_x=vel_x;
	this->vel_y=vel_y;
	currentState = in;
	flip = SDL_FLIP_NONE;

	//TODO change hardcoded mid screen width point
	if ( spawnpos_x < (400-(texture->getWidth()/2)) ){
		flip = SDL_FLIP_HORIZONTAL;
	}
}



bool Enemy::leftTheScreen(){
	if ((pos_x+(entityTexture->getWidth())<0) || 
		(pos_y+(entityTexture->getHeight())<0) ||
		(pos_x>DEFAULT_RESOLUTION_WIDTH) ||
		(pos_y>DEFAULT_RESOLUTION_HEIGHT) ){
			return true;
	} else {
			return false;
	}
}



void Enemy::handleInScreenState(){
	NotifyDebug("El enemigo tiene posicion: (" + to_string(pos_x) + " , " +to_string(pos_y) + ").", GetEnviroment(__FILE__, __FUNCTION__));

	if (leftTheScreen()){
		//desaparecio de la pantalla??
		NotifyDebug("El enemigo salio de la pantalla.", GetEnviroment(__FILE__, __FUNCTION__));
		currentState = out;
	}else{
		pos_x+=vel_x;
		pos_y+=vel_y;
	}
}


void Enemy::handleOutState(){
}

void Enemy::handleDeathState(){

}

void Enemy::handleStates(){
	switch (currentState)	{
		case in:
			handleInScreenState();
			break;
		case out:
			handleOutState();
			break;
		case death:
			handleDeathState();
			break;
	}
}


void Enemy::renderInScreenState(){
	entityTexture->render(pos_x,pos_y,NULL,NULL,NULL,flip);
}

void Enemy::renderOutState(){
	//POSIBLE ESTADO AL SALIR DE PANTALLA?
}

void Enemy::renderDeathState(){
	//TODO MUERTE ENEMIGO

}

void Enemy::renderStates(){
	switch (currentState)	{
		case in:
			renderInScreenState();
			break;
		case out:
			renderOutState();
			break;
		case death:
			renderDeathState();
			break;
	}
}



Enemy::STATES Enemy::CurrentState(){
	return currentState;
}



void Enemy::move(){
	handleStates();
}

void Enemy::render(){
	renderStates();
}