#include "Level.h"

 Level::Level(Background* aBackground){

    this->background = aBackground;
    this->Attach();
}

 Level::~Level(){
    background->close();
	
	//TODO: kill entities
}

Background* Level::getBackground(){
	return background;
}


levelConfig_t Level::getConfig(){
    return config;
}

void Level::setConfig(levelConfig_t levelConfig){
    this->config = levelConfig;
}

void Level::setContinuePath(std::string path){
    this->continuePath = path;
}

std::string Level::getContinuePath(){
    return this->continuePath;
}


void Level::setBackground(Background* background){
    this->background = background;
}

void Level::setEnemyMenager(EnemyManager* enemyManager){
    this->enemyManager = enemyManager;
}

EnemyManager* Level::getEnemyManager(){
    return this->enemyManager;
}




