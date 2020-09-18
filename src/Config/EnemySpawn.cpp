#include "EnemySpawn.h"

EnemySpawn::EnemySpawn(std::string type, int time, int spawnPosX, int spawnPosY, int velX, int velY){
    this->enemyType = type;
    this->spawnTime = time;
    this->spawnPosX=spawnPosX;
    this->spawnPosY=spawnPosY;
    this->velX=velX;
    this->velY=velY;
}

EnemySpawn::EnemySpawn(){
    //hardcodear default??
}

void EnemySpawn::setSpawnTime(int time){
    spawnTime=time;
}

std::string EnemySpawn::getEnemyType(){
    return enemyType;
} 

int EnemySpawn::getSpawnPosX(){
    return spawnPosX;
} 

int EnemySpawn::getSpawnPosY(){
    return spawnPosY;
} 

int EnemySpawn::getVelX(){
    return velX;
} 

int EnemySpawn::getVelY(){
    return velY;
} 

int EnemySpawn::getSpawnTime(){
    return spawnTime;
} 
