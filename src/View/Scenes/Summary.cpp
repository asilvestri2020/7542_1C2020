
#include "Summary.h"

Summary::Summary(SDL_Renderer* aRenderer, SceneManager* aManager){
    sceneManager = aManager;
    renderer = aRenderer;

    // Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de Summary", GetEnviroment(__FILE__, __FUNCTION__));
}

Summary::~Summary(){

    continueTexture->free();

     // Detach to loggerObserver
	NotifyDebug("Destructor de Summary llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();
}

void Summary::eventHandler(SDL_Event& e ){

    //ENTER PARA AVANZAR AL SIGUIENTE JUEGO Y D PARA """DEBUGGEAR"""

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
        NotifyInfo("Se avanza al siguiente juego debido a ENTER del usuario.", GetEnviroment(__FILE__, __FUNCTION__));
        //sceneManager->changeTo(GAME_SCENE);
        
        sceneManager->changeWithTransition(SUMMARY_SCENE,GAME_SCENE,1500);
    }
    
    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d ){
        NotifyInfo("Modo debug en el Resumen", GetEnviroment(__FILE__, __FUNCTION__));
    }
}

void Summary::update(){

}

void Summary::render(){
    continueTexture->render(0,0);
}

bool Summary::loadSceneResources(){
    continueTexture = new LTexture(renderer);
    return continueTexture->loadFromFile(sceneManager->getConfiguration()->getNextLevelContinueTexture()
    ,DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT);
}

bool Summary::loadSceneResources(string path){
    continueTexture = new LTexture(renderer);

    return continueTexture->loadFromFile(path, this->sceneManager->getWindow()->getWidth(), 
    this->sceneManager->getWindow()->getHeight());
}

void Summary::startScene(){
    this->loadSceneResources();
}

