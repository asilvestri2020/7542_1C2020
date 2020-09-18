#include "EnemyManager.h"
  
EnemyManager* EnemyManager::instance = nullptr;

EnemyManager* EnemyManager::getInstance(){
	if (instance == nullptr){
		instance = new EnemyManager();
	}
	return instance;
}

EnemyManager::~EnemyManager(){
	delete instance;
	instance = nullptr;

	// Detach to loggerObserver
	NotifyDebug("Destructor de LTexture llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();
}

EnemyManager::EnemyManager(){
	srand(time(0));
  	Attach();
	NotifyDebug("Incializada una instancia de EnemyManager", GetEnviroment(__FILE__, __FUNCTION__));
}

void EnemyManager::loadMedia(vector<enemy_t> enemies){
	std::string enviroment = this->GetEnviroment(__FILE__, __FUNCTION__);
	for (int i = 0; i < enemies.size(); ++i){
		if (textures[enemies[i].type]==nullptr){
			textures[enemies[i].type] = new LTexture(this->renderer);
			if (!textures[enemies[i].type]->loadFromFile(enemies[i].path)){
				//DESHACER EL MAPPING
        		NotifyError("Fallo la carga de imagen "+ enemies[i].path+" de "+enemies[i].type, enviroment);
			}else{
				//totalEnemyTypes++;
        		NotifyDebug("Enemigo agregado, se cargo la imagen "+ enemies[i].path+" de " +enemies[i].type, enviroment);
			}
		}else{
     		NotifyError("Tipo de enemigo duplicado "+ enemies[i].type, enviroment);
		}		
	}
}

void EnemyManager::setConfig(std::vector<EnemySpawn*> setupConfig){
	config=setupConfig;
	spawnIndex=0;
	enemies.clear(); //revisar memoria?
	state=PLAYING;
}

void EnemyManager::setRenderer(SDL_Renderer* renderer){
	this->renderer = renderer;
}

void EnemyManager::spawnEnemy(int pos_x, int pos_y, int vel_X, int vel_y, std::string enemyType){
	addEnemy(pos_x,pos_y,vel_X,vel_y,textures[enemyType]);
}

void EnemyManager::addEnemy(int pos_x, int pos_y, int vel_X, int vel_y, LTexture* texture){
	if (pos_y+(texture->getHeight()) > DEFAULT_RESOLUTION_HEIGHT) { //Enemigo cortado en eje x?
		int diff = ((pos_y + (texture->getHeight())) - DEFAULT_RESOLUTION_HEIGHT);
		enemies.push_back(new Enemy(pos_x,pos_y-diff,vel_X,vel_y,texture));
		return;
	}
	enemies.push_back(new Enemy(pos_x,pos_y,vel_X,vel_y,texture));
	
	std::string enviroment = this->GetEnviroment(__FILE__, __FUNCTION__);
	std::string message = string("Se spawneo un enemigo en ("+to_string(pos_x)+","+to_string(pos_y)+"). Ahora hay "+to_string(enemies.size())+" enemigos");
	NotifyDebug(message, enviroment);
}

int EnemyManager::getRandomNumber(int to){
	if (to==0){return 0;}
	//devuelve random number entre 0 y to
	if (to>0){
		return (rand() % to +(rand()%2));
	}else{
		//devuelve random number entre -to y to+1
		return (rand() % (((to)*(-2))+1) +to);
	}
}

void EnemyManager::setTimer(UtilTimer* timer){
	this->timer=timer;
}

void EnemyManager::update(){
	checkEnemySpawn();
	updateEnemies();
}

//SPAWN ENEMY LOGIC
void EnemyManager::checkEnemySpawn(){
	if (spawnIndex < config.size()){
		if (config[spawnIndex]->getSpawnTime() < timer->getTicks()){
			spawnEnemy(config[spawnIndex]->getSpawnPosX(),
						config[spawnIndex]->getSpawnPosY(),
						config[spawnIndex]->getVelX(),
						config[spawnIndex]->getVelY(),
						config[spawnIndex]->getEnemyType());
			spawnIndex++;
		}
	}else{
		if (activeEnemies == 0){
			state=CLEARED;
       		NotifyDebug("LEVEL CLEARED: No hay mas enemigos para spawnear ni enemigos activos en pantalla.", GetEnviroment(__FILE__, __FUNCTION__));
		}
	}
}

void EnemyManager::updateEnemies(){
	for (int i = 0; i < enemies.size(); ++i){
		activeEnemies = 0;
		enemies[i]->move();
		if (enemies[i]->CurrentState() == Enemy::in){
			activeEnemies++;
		}
	}
}

//LOGICA PARA DISTRIBUIR ENEMIGOS A LO LARGO DE LA DURACION DEL NIVEL
void EnemyManager::distributeEnemies(levelConfig_t levelConfig){
	std::vector<EnemySpawn*> enemies;
	int enemySpawnDelay = levelConfig.duration/levelConfig.numberOfEnemies;
	int screenSide = DEFAULT_RESOLUTION_WIDTH;
	for (int enemyIndex=0; enemyIndex<levelConfig.numberOfEnemies; enemyIndex++){
		string enemyType = levelConfig.enemies[getRandomNumber(levelConfig.enemies.size()-1)].type;
		float direction = -1.0;
		if (levelConfig.bothDirections) {
			screenSide = (getRandomNumber(1) ? (0-textures[enemyType]->getWidth()) : DEFAULT_RESOLUTION_WIDTH);
			direction = ((screenSide==DEFAULT_RESOLUTION_WIDTH) ? -1.0 : 0.66); //PARA QUE LADO VA EL ENEMIGO multiplicando la velocidad
		}
		enemies.push_back(
			new EnemySpawn(
				enemyType,
				enemySpawnDelay*(enemyIndex+1),
				screenSide,
				getRandomNumber(DEFAULT_RESOLUTION_HEIGHT),
				(direction)*levelConfig.backgrounds[4].velocity,
				0
			)
		);
	}

	setConfig(enemies);
	NotifyInfo("Se distribuyeron los enemigos para el nivel "+to_string(levelConfig.number), GetEnviroment(__FILE__, __FUNCTION__));
}

EnemyManagerState EnemyManager::getState(){
	return state;
}

void EnemyManager::render(){
	for (int i = 0; i < enemies.size(); ++i)
		enemies[i]->render();
}