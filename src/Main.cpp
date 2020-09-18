#include <SDL2/SDL.h>
#include <string>
#include <cstring>
#include <memory>
#include "Utils/Common.h"
#include "Utils/LoggerObserver.h"
#include "Utils/UtilTimer.h"
#include "Model/Model.h"

#include "View/Window.h"
#include "Utils/SceneManager.h"
#include "Parser/Parser.h"


Common common;

//Global Window and global SceneManager
Window gWindow;

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

int main(int argc, char *args[]) {
    //default log level
    int logDefaultLevel = 3;
    int loggerLevel;

    //Initialize log
    LoggerObserver *loggerObserver;
    loggerObserver = loggerObserver->getInstance();
    std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
    loggerObserver->updateLevel(logDefaultLevel);
    loggerObserver->writeInfoLine("Previo a obtener la configuración ponemos el log en el modo más abarcativo.",
                                  enviroment);

    //Json Parser
    std::shared_ptr<Parser> config(new Parser());
    config->loadConfig();

    if (argc > 1) {
        loggerLevel = atoi(getCmdOption(args, args + argc, "-logger"));
        if (1 <= loggerLevel && loggerLevel <= 3) {
            logDefaultLevel = loggerLevel;
            loggerObserver->writeInfoLine(
                    "Se setea el nivel del log cargado por linea de comando luego de la lectura del archivo de config: " +
                    std::to_string(loggerLevel), enviroment);
            loggerObserver->updateLevel(loggerLevel);
        }else{
            loggerObserver->writeErrorLine("Nivel de log invalido, se setea a nivel por defecto: 3",enviroment);
            loggerObserver->updateLevel(logDefaultLevel);
        }
    } else {
        loggerObserver->updateLevel(config->getLoggerLevel());
        loggerObserver->writeInfoLine("Se setea nivel de log cargado por archivo de configuracion", enviroment);
    }

    resolutionConfig_t resolutionConfig = config->getResolutionConfig();
    int fps = config->getFps();
    UtilTimer *timer = new UtilTimer();

    //Start up SDL and create window
    loggerObserver->writeDebugLine("Iniciamos DSL y creamos la ventana.", enviroment);
    if (!gWindow.init(resolutionConfig.width, resolutionConfig.height)) {
        return 1;
    }

    //Creates SceneManager
    loggerObserver->writeDebugLine("Creamos el manager para las escenas.", enviroment);
    SceneManager gSceneManager(gWindow.getRenderer(), &gWindow, config);

    //Load resources
    loggerObserver->writeDebugLine("Cargamos los recursos a utilizar.", enviroment);
    if (!gSceneManager.loadScenesResources()) {
        return 1;
    }

    Scene *actualScene = NULL;
    gSceneManager.setActualScenePtr(&actualScene);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    loggerObserver->writeDebugLine("Iniciamos el loop principal del juego.", enviroment);
    while (!quit) {

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {

            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
                loggerObserver->writeInfoLine("Solicitud de salir del juego por accion del usuario.", enviroment);
            }
            actualScene->eventHandler(e);

        }

        actualScene->update();

        gWindow.clearScreen();

        actualScene->render();

        gWindow.renderScreen();
        //If we want to cap the frame rate
        if (timer->getTicks() < 1000 / fps) {
            //Sleep the remaining frame time
            SDL_Delay((1000 / fps) - timer->getTicks());
        }

    }

    //close SDL
    gWindow.close();

    loggerObserver->writeInfoLine("Saliendo del juego", enviroment);
    return 0;
}


