#ifndef _ENEMY_H
#define _ENEMY_H
#include "Entity.h"
#include <stdio.h>
#include "../../Parser/Default_values.h"


class Enemy: public Entity{
public:
	enum STATES { in, out, death };
	enum TYPES { ship, boss };

protected:
	//static Player* player;

	//Timer* timer;

	STATES currentState;

	int currentPath;


protected:

	void handleInScreenState();
	void handleOutState();
	void handleDeathState();

	void handleStates();


	void renderInScreenState();
	void renderOutState();
	void renderDeathState();
	
	void renderStates();

    
	bool leftTheScreen();


public:

	
	Enemy(int spawnXPos, int spawnYPos, int velX, int velY, LTexture* texture);


	STATES CurrentState();
	TYPES Type();
	int index();



	void move();
	void render();
};

#endif