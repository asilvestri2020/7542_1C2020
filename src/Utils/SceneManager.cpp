#include "SceneManager.h"
#include "../View/Scenes/Menu.h"
#include "../View/Scenes/Game.h"
#include "../View/Scenes/Summary.h"
#include "../View/Scenes/Transition.h"



SceneManager::SceneManager(SDL_Renderer* aRenderer, Window* aWindow, std::shared_ptr<Parser> config){
    
    //TODO: cuando window sea SINGLETON no seran   
    //      necesario los atributos del constructor
    gameTimer = new UtilTimer();
    window = aWindow;
    // Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de SceneManager", GetEnviroment(__FILE__, __FUNCTION__));

    window = aWindow;
    this->config = config;
    if(TOTAL_SCENES == 0)return;

    //Malloc of the needed pointers (Scene*)
    scenesList = (Scene**) malloc(sizeof(Scene*) * TOTAL_SCENES);

    //Initialice the vector
    
    for (int i = 0; i < TOTAL_SCENES; i++){
        
        scenesList[i] = initScene((Scenes)i,aRenderer);
        
    }

}


SceneManager::~SceneManager(){

    if(TOTAL_SCENES == 0)return;

    //Calls to the decontructor of each scene
    for (int i = 0; i < TOTAL_SCENES; i++) delete scenesList[i];

    //Free the list of scenes
    free(scenesList);

    // Detach to loggerObserver
	NotifyDebug("Destructor de SceneManager llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();
}

void SceneManager::setActualScenePtr(Scene** anActualScenePtr){

    //Saves the pointer to the actualScene in Main.c
    actualScene = anActualScenePtr;

    //Set the first scene to startup
    changeTo(MENU_SCENE);

}


UtilTimer* SceneManager::getGameTimer(){
    return gameTimer;
}

void SceneManager::handleChangeToTimer(Scenes scene){
    switch (scene){

        case MENU_SCENE:
            gameTimer->stop();
            break;

        case GAME_SCENE:
            gameTimer->start();                          
            break;

        case SUMMARY_SCENE:
            gameTimer->stop();
            break;

        case TOTAL_SCENES:
            //gameTimer->pause();??
            break;

        default:
            break;
    }
}


void SceneManager::changeTo(Scenes scene){
    *actualScene = scenesList[scene];
    handleChangeToTimer(scene);
}

//Direct changing scene by pointer
void SceneManager::changeTo(Scene* scene){
    *actualScene = scene;
 
     
}

//Transition changing scene by IDs
void SceneManager::changeWithTransition(Scenes fromScene, Scenes toScene,int time){
    Transition* transition = (Transition*) scenesList[TRANSITION_SCENE];
    transition->setTransition(scenesList[fromScene],scenesList[toScene],time);

    changeTo(TRANSITION_SCENE);
    handleChangeToTimer(toScene);

}


Scene* SceneManager::initScene(Scenes scene, SDL_Renderer* renderer){

    Scene* newScene = NULL;

    switch (scene){

    case MENU_SCENE:
        newScene = new Menu(renderer,this);
        break;

    case GAME_SCENE:
        newScene = new Game(renderer,this,window);
        break;

    case SUMMARY_SCENE:
        newScene = new Summary(renderer,this);;
        break;
    
    case TRANSITION_SCENE:
        newScene = new Transition(renderer,this);
        break;

    default:
        NotifyError("ERROR: the selected scene is ilegal", GetEnviroment(__FILE__, __FUNCTION__));
        break;
    }

    return newScene;
}


bool SceneManager::loadScenesResources(){

    bool succes = true;
    std::string enviroment = GetEnviroment(__FILE__, __FUNCTION__);

    for (int i = 0; i < TOTAL_SCENES; i++){
        
        if(!scenesList[i]->loadSceneResources()){
            std::string message = "The scene nro " + to_string(i) + " couldn't load his resources.";
            NotifyError(message, enviroment);
            succes = false;
        }
    }

    

    if (succes) {
        NotifyDebug("Cargados los recursos del sceneManager. Se crearon las escenas.", enviroment);
    } else {
        NotifyError("Fallo al cargar los recursos del sceneManager", enviroment);
    }
    return succes;
}

Window* SceneManager::getWindow(){
    return window;
}

Scene* SceneManager::getScene(){
    return *actualScene;
}

std::shared_ptr<Parser> SceneManager::getConfiguration(){
    return this->config;
}

Scene* SceneManager::getActualScene(){
    return *actualScene;
}