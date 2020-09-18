
#include "Game.h"
#include "Summary.h"

#define SUMMARY_TIME_TANSITION 1500
#define MENU_TIME_TANSITION 0

Game::Game(SDL_Renderer* aRenderer, SceneManager* aManager, Window* aWindow){
    sceneManager = aManager;
    renderer = aRenderer;
    
    window = aWindow;


    enemyManager = EnemyManager::getInstance();
    enemyManager->setRenderer(renderer);
    enemyManager->setTimer(aManager->getGameTimer());
    

    levels = loadLevels(aManager);
	NotifyInfo("Niveles cargados.", GetEnviroment(__FILE__, __FUNCTION__));

    int totalLevels = levels.size();

    if(totalLevels <= 0){
        //terminar esta escena con un mensaje de error y volver al menu
    }

    //Level "pointer" to the first one
    actual = 0;
    paused = false;
    enemyManager->distributeEnemies(levels[actual]->getConfig());

    // Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de Game", GetEnviroment(__FILE__, __FUNCTION__));
    
}

Game::~Game(){

    for (int i = 0; i < levels.size(); i++){
       levels[i]->getBackground()->close();
    }
    
    shipTexture->free();
	//enemyManager->free();

    // Detach to loggerObserver
	NotifyDebug("Destructor de Game llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();
}

bool Game::loadSceneResources(){

    pauseTexture = new LTexture(renderer);

    pauseTexture->loadFromFile(sceneManager->getConfiguration()->getPauseTexture(),DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT);
	NotifyInfo("Pause texture: " + sceneManager->getConfiguration()->getPauseTexture(), GetEnviroment(__FILE__, __FUNCTION__));

    shipTexture = new LTexture(renderer);
	NotifyInfo("Ship texture: " + sceneManager->getConfiguration()->getShipTexture(), GetEnviroment(__FILE__, __FUNCTION__));
    shipTexture->loadFromFile(sceneManager->getConfiguration()->getShipTexture());

    player = new Ship(shipTexture,0,0);

    //TODO: no hardcodear el true
    return true; 
}

void Game::eventHandler(SDL_Event& e){

    if(e.type == SDL_KEYDOWN){
        
        switch (e.key.keysym.sym){

        case SDLK_RETURN:
            //Toggle pause mode only once for pressed key
            if(!e.key.repeat){
                paused = !paused;
                if ( paused ) {
                    sceneManager->getGameTimer()->pause();
                }else{
                    sceneManager->getGameTimer()->unpause();
                }
            } 
            break;

        case SDLK_n:
            NotifyDebug("Nuevo nivel inicializado por accion de usuario", GetEnviroment(__FILE__, __FUNCTION__));
            sceneManager->changeWithTransition(GAME_SCENE,SUMMARY_SCENE,SUMMARY_TIME_TANSITION);
            break;

        case SDLK_q:
            NotifyDebug("Menu presentado por accion de usuario", GetEnviroment(__FILE__, __FUNCTION__));
            sceneManager->changeWithTransition(GAME_SCENE,MENU_SCENE,MENU_TIME_TANSITION);
            break;

        case SDLK_x:
            updateEntitiesByKeyState();
            break;

        default:
            break;
        }

    }

    player->handleEvent(e);
}

void Game::update(){
    

    if(paused)return;

    player->update(DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT);
    levels[actual]->getEnemyManager()->update();
	levels[actual]->getBackground()->update();

    //LOGICA TERMINAR NIVEL
    if (enemyManager->getState()==CLEARED){
        sceneManager->getConfiguration()->setNextLevelContinueTexture(levels[actual]->getContinuePath());
        sceneManager->changeWithTransition(GAME_SCENE,SUMMARY_SCENE,SUMMARY_TIME_TANSITION);

    }
}

void Game::render(){
    //esta bien renderizar por mas que se este pauseado??
    levels[actual]->getBackground()->render();
    levels[actual]->getEnemyManager()->render();
    player->render();
    

    if(paused){
        //Screen showed on pause 

        pauseTexture->render(0,0);
        //(if that screen have not transparency, then this statment 
        //can be on top because the game wont need to be rendered)
    }
}

vector<Level*> Game::loadLevels(SceneManager* aManager){
    vector<Level*> newLevels = vector<Level*>();
    
    std::vector<levelConfig_t> levels = aManager->getConfiguration()->getLevelConfigVector();

    for(int i =0; i < levels.size(); i++){
        //set background
        levelConfig_t levelConfig = levels[i];
        Background* background = new Background(renderer);
        background->loadMedia(levelConfig.backgrounds,DEFAULT_RESOLUTION_WIDTH,DEFAULT_RESOLUTION_HEIGHT);


        //ENEMYMANAGER
        enemyManager->loadMedia(levelConfig.enemies);


        Level* level = new Level(background);
        level->setEnemyMenager(enemyManager);
        level->setConfig(levelConfig);
        level->setContinuePath(levelConfig.continueTexture);
        newLevels.push_back(level);
    
    }    

    return newLevels;
}

void Game::updateEntitiesByKeyState(){

    //Llamada turbia a SDL.. no se me ocurrio otra manera(?)
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //state = {vel_x = -1/0/1 , vel_y = -1/0/1 }
    int state[2] = { 0, 0 };
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) state[0] -= 1;
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) state[0] += 1;
    if( currentKeyStates[ SDL_SCANCODE_UP ] ) state[1] -= 1;
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) state[1] += 1;

    player->setVelocity(state[0],state[1]);
}

//Inicializacion de cada nivel
void Game::startScene(){

    delete player;

    player = new Ship(shipTexture,(window->getWidth()-shipTexture->getWidth())/4,
                                (window->getHeight()-shipTexture->getHeight())/2);

    updateEntitiesByKeyState();
}

//Logica de cambio de nivel o reseteo del juego en caso de haber perdido
void Game::finishScene(){

    actual++;
    if(actual >= levels.size())actual = 0;
    enemyManager->distributeEnemies(levels[actual]->getConfig());

}