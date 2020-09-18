#include "Background.h"
#include <stdio.h>
#include <vector>

using namespace std;

Background::Background(SDL_Renderer* renderer){
	
	this->gRenderer = renderer;

}


Background::~Background(void){

}

bool Background::loadMedia(std::vector<backgroundConfig_t> confs, int screenWidth,int screenHeight){
	
	//Loading success flag
	bool success = true;

	int layers = confs.size();
	
	// TODO: revisar estas lineas no me cierra el casteo
	scrollingOffsets =  (int*) malloc(sizeof(int)*layers);
	scrollingVelocity = (int*) malloc(sizeof(int)*layers);

	for(int i= 0; i < layers; i++){

		LTexture* texture = new LTexture(gRenderer);
		//Load background texture
		if( !texture->loadFromFile(confs[i].path,DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT) ){
			success = false;
		}

		//Sets parameters of each layer
		scrollingOffsets[i] = 0;
		scrollingVelocity[i] = (confs[i].velocity);
	
		//Stores layer
		bgTextures.push_back(texture);

	}

	return success;
}

void Background::close(){

	int layers = this->bgTextures.size();
	if( layers <= 0) return;

	//Free loaded images
	for(int i= 0; i < layers; i++){
		this->bgTextures[i]->free();
	}

	//Free parameters
	free(scrollingOffsets);
	free(scrollingVelocity);
}

void Background::update(){

	for(int i=0; i< this->bgTextures.size(); i++){ 
		    
		scrollingOffsets[i] -= scrollingVelocity[i];
	 
		if(scrollingOffsets[i] < -this->bgTextures[i]->getWidth()){
			scrollingOffsets[i] = 0;
		}
	
	}

}

void Background::render(){
	
	//Render background (temporal)
	for(int i=0; i < this->bgTextures.size(); i++){ 
		    
	
		//Render background
		this->bgTextures[i]->render(scrollingOffsets[i] , 0);
		this->bgTextures[i]->render(scrollingOffsets[i] + this->bgTextures[i]->getWidth(), 0);
		
	}

}
