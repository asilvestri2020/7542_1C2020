
#ifndef _GAME_HEADER
#define _GAME_HEADER

#include "../../Model/Entities/Ship.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/LTexture.h"
#include "../../Utils/EnemyManager.h"
#include "../../Utils/LoggerSubject.h"
#include "../../Model/Entities/Level.h"
#include "../Window.h"
#include "Scene.h"

//TODO: keep track of game stats
//TODO: organizar niveles 

class Game: public LoggerSubject, public Scene {

    //Read
    public:

        //TODO: cuando window sea SINGLETON ya no se necesitaran los punteros a
        // renderer ni a window.
        Game(SDL_Renderer* aRenderer, SceneManager* aManager, Window* aWindow);
        ~Game();

        void update();
        void render();
        void eventHandler(SDL_Event& e );
        bool loadSceneResources();  
        void startScene();
        void finishScene();

        vector<Level*> loadLevels(SceneManager* aManager);

    private:
    
        void updateEntitiesByKeyState();

        LTexture* pauseTexture;
        LTexture* shipTexture;
        Ship* player;
        EnemyManager* enemyManager;

        bool paused;

        vector<Level*> levels;
        int actual;

        //temp:
        Window* window;
        SceneManager* sceneManager;
        SDL_Renderer* renderer;
};

#endif