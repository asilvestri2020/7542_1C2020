
#ifndef LEVEL_HEADER
#define LEVEL_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../../View/Background.h"

#include "../../Config/BackgroundConfig.h"
#include "../../Config/EnemySpawn.h"
#include "Entity.h"
#include "../../Utils/EnemyManager.h"



//Level works like a structure with the data that identify itself. i.e
//Name or number, background, entities.

class Level : public LoggerSubject {

    public:
        Level(Background* aBackground);
        ~Level();
        
        void setBackground(Background* aBackground);
        void setEnemyMenager(EnemyManager* enemyManager);
        EnemyManager* getEnemyManager();
        Background* getBackground();
        std::vector<Entity*> getEntities();
        void setConfig(levelConfig_t levelConfig);
        levelConfig_t getConfig();
        void setContinuePath(std::string path);
        std::string getContinuePath();

    private:
        levelConfig_t config;
        Background* background;
	std::vector<Entity*> entities;
        int levelDuration;
        EnemyManager* enemyManager;
        std::string continuePath;

};

#endif