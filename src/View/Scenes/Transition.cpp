
#include "Transition.h"

Transition::Transition(SDL_Renderer* aRenderer, SceneManager* aManager){
    this->renderer = aRenderer;
    this->sceneManager = aManager;
}

void Transition::setTransition(Scene *aScene1, Scene *aScene2, int aDuration){

    scene1 = aScene1;
    scene2 = aScene2;
    
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

    //Total_frames for each transition (first fadeout and then fadein)
    total_frames = (aDuration*FPS)/1000/2;
    faddingOut = true;
    frames = 0;

}
bool Transition::loadSceneResources(){
    return true;
}
void Transition::eventHandler(SDL_Event& e ){

    if(!faddingOut) scene2->eventHandler(e);
}

void Transition::update(){
    //If frames is 0 and is not fadding out, then the transition finished.
    if(frames <= 0 && !faddingOut){
        sceneManager->changeTo(scene2);
    }

    if(faddingOut)frames++;
    else frames--;

    if(frames >= total_frames){
        faddingOut = false;
        scene1->finishScene();
        scene2->startScene();   
    }
}
void Transition::render(){

    //If is still fadding out the first scene, render it
    if(faddingOut)scene1->render();
    else scene2->render();

    //Fadding out/in the scenes
    Uint8 factor_alpha = ((float)frames/total_frames)*0xFF;
    SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,factor_alpha);
    SDL_RenderFillRect(renderer,NULL);

}
