#include "EnemiesTypeConfig.h"

EnemiesTypeConfig::EnemiesTypeConfig(std::string type, std::string filePath){
    this->enemyType = type;
    this->filePath = filePath;
}

std::string EnemiesTypeConfig::getEnemyType(){
    return enemyType;
} 

std::string EnemiesTypeConfig::getFilePath(){
    return filePath;
} 


