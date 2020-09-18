
#ifndef _SUMMARY_HEADER
#define _SUMMARY_HEADER

#include "Scene.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/LTexture.h"
#include "../../Utils/LoggerSubject.h"

class Summary: public Scene, public LoggerSubject  {

    public:

        Summary(SDL_Renderer* aRenderer, SceneManager* aManager);
        ~Summary();

        void update();
        void render();
        void eventHandler(SDL_Event& e );
        bool loadSceneResources();
        bool loadSceneResources(string path);
        void startScene();

   
    private:

        LTexture* continueTexture;
        SceneManager* sceneManager;
        SDL_Renderer* renderer;
};

#endif