
#ifndef _MENU_HEADER
#define _MENU_HEADER

#include "Scene.h"
#include "../../Utils/LTexture.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/LoggerSubject.h"

class Menu: public Scene, public LoggerSubject {

    public:

        Menu(SDL_Renderer* aRenderer, SceneManager* aManager);
        ~Menu();

        void update();
        void render();
        void eventHandler(SDL_Event& e );
        bool loadSceneResources();
   
    private:

        LTexture* startTexture;
        SceneManager* sceneManager;
        SDL_Renderer* renderer;
};

#endif