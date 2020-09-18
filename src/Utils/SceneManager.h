#ifndef SCENE_MANAGER_HEADER
#define SCENE_MANAGER_HEADER

#include "UtilTimer.h"
#include "../View/Scenes/Scene.h"
#include "../View/Window.h"
#include "LoggerSubject.h"
#include "../Parser/Parser.h"
#include <memory>



enum Scenes{

    MENU_SCENE,
    GAME_SCENE,
    SUMMARY_SCENE,
    TRANSITION_SCENE,
    TOTAL_SCENES        //Always at the bottom
    
};

class SceneManager: public LoggerSubject {

    public:

        //Sets the first scene (menu)
        SceneManager(SDL_Renderer* renderer,Window* aWindow, std::shared_ptr<Parser> confg);
        ~SceneManager();

        bool loadScenesResources();

        //When the actual scene finish its work and needs to sets the
        //next one scene, it can call the changeTo() method for a direct changing
        //or also can call the changeWithTransition() for a fadeout/fadein
        //scenes transition.
        void changeTo(Scenes scene);
        void changeTo(Scene* scene);
        void changeWithTransition(Scenes fromScene, Scenes toScene,int time);

        void setActualScenePtr(Scene** anActualScenePtr);

        UtilTimer* getGameTimer();
        Scene* getScene();
        Window* getWindow();
        std::shared_ptr<Parser> getConfiguration();
        Scene* getActualScene(); 

    private:

        Scene* initScene(Scenes scene, SDL_Renderer* renderer);
        void killScene();
        void handleChangeToTimer(Scenes scene);

        //This is a reference to the actualScene variable in Main.c
        //Allows to update the pointer to the correct scene according to
        //the game's flow. 
        Scene** actualScene;

        //The list of Scenes pointers avaibles. This variable point to a vector 
        //of size TOTAL_SCENES
        Scene** scenesList;
        Window* window;
        std::shared_ptr<Parser> config;

        UtilTimer* gameTimer;

};

#endif