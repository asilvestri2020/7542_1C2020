#include "BackgroundConfig.h"

 BackgroundConfig::BackgroundConfig(){
     path = "";
     velocity = 0;
 }
BackgroundConfig::~BackgroundConfig(){
    
}
void BackgroundConfig::setPath(std::string path){
    this->path = path;
}
void BackgroundConfig::setVelocitiy(int vel){
    this->velocity = vel;
}
std::string BackgroundConfig::getPath(){
    return this->path;
}
int BackgroundConfig::getVelocity(){
    return this->velocity;
}