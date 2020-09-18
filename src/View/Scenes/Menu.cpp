
#include "Menu.h"

Menu::Menu(SDL_Renderer* aRenderer, SceneManager* aManager){
    sceneManager = aManager;
    renderer = aRenderer;

    // Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de Menu", GetEnviroment(__FILE__, __FUNCTION__));
}

Menu::~Menu(){

    startTexture->free();

     // Detach to loggerObserver
	NotifyDebug("Destructor de Menu llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();
}

void Menu::eventHandler(SDL_Event& e ){

    //ENTER PARA AVANZAR AL JUEGO Y D PARA """DEBUGGEAR"""
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
        NotifyInfo("Se avanza con el juego debido a ENTER del usuario.", GetEnviroment(__FILE__, __FUNCTION__));
        //sceneManager->changeTo(GAME_SCENE);
        sceneManager->changeWithTransition(MENU_SCENE,SUMMARY_SCENE,3000);

    }

    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d ){
        NotifyInfo("Modo debug en el Menu", GetEnviroment(__FILE__, __FUNCTION__));
    }
}

void Menu::update(){

}

void Menu::render(){
    
    startTexture->render(0,0);
}

bool Menu::loadSceneResources(){

    bool success = true;

    startTexture = new LTexture(renderer);

    success = startTexture->loadFromFile(sceneManager->getConfiguration()->getStartTexture(),DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT);
    NotifyInfo("Start texture: " + sceneManager->getConfiguration()->getStartTexture(), GetEnviroment(__FILE__, __FUNCTION__));

    return success;
}
