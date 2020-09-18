#ifndef _SCENE_TRANSITION
#define _SCENE_TRANSITION

#include "Scene.h"
#include "../../Utils/LTexture.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/LoggerSubject.h"


class Transition: public LoggerSubject, public Scene{

    public:

        Transition(SDL_Renderer* aRenderer, SceneManager* aManager);

        void setTransition(Scene *aScene1, Scene *aScene2, int frames);
        bool loadSceneResources();
        void eventHandler(SDL_Event& e );
        void update();
        void render();
        
    private:

        static const int FPS = 60;

        bool faddingOut;
        int total_frames;
        int frames;
        Scene *scene1, *scene2;
        SceneManager* sceneManager;
        SDL_Renderer* renderer;
};

#endif