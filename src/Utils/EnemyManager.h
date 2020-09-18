#ifndef _ENEMYMANAGER_H
#define _ENEMYMANAGER_H
#include <map>


#include <stdio.h>
#include <string>
#include "../Model/Entities/Enemy.h"
#include "../View/Background.h"
#include "../Model/Entities/Enemy.h"
#include "../Config/EnemySpawn.h"
#include "UtilTimer.h"

enum EnemyManagerState{
    CLEARED,
    PLAYING    
};


class EnemyManager: public LoggerSubject {
	private:
		int activeEnemies;
		//int totalEnemyTypes;
		int spawnIndex;
		std::map<std::string, LTexture*> textures;
		static EnemyManager* instance;
		SDL_Renderer* renderer;
		std::vector<Enemy*> enemies;
		std::vector<EnemySpawn*> config;
		UtilTimer* timer;
		EnemyManagerState state;
	public:
		void loadMedia(vector<enemy_t> enemies);
		EnemyManagerState getState();
		static EnemyManager* getInstance();
		static void Release();
		void setTimer(UtilTimer* timer);
		void setRenderer(SDL_Renderer* renderer);
		void update();
		void render();
		void setConfig(std::vector<EnemySpawn*> config);
		int getRandomNumber(int to);
		void distributeEnemies(levelConfig_t levelConifg);
	private:
		EnemyManager();
		void addEnemy(int xpos, int ypos, int xvel, int yvel, LTexture* enemyTypeTexture);
		void spawnEnemy(int xpos, int ypos, int xvel, int yvel, std::string enemyType);
		void checkEnemySpawn();
		void updateEnemies();
		~EnemyManager();
		std::string path;
};
#endif