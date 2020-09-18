#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "../Utils/LoggerSubject.h"

#include "../Utils/Common.h"
#include "Default_values.h"

#define MAIN_FILE_NAME "Parser/config.json"
#define BACKUP_FILE_NAME "Parser/backup_config.json"

using namespace std;

struct resolutionConfig_t {
    int height;
    int width;
};

struct backgroundConfig_t {
    string path;
    int velocity;
};

struct enemy_t {
    string path;
    string type;
};

struct levelConfig_t {
    bool bothDirections;
    vector<enemy_t> enemies;
    string continueTexture;
    int number;
    int duration;
    int numberOfEnemies;
    vector<backgroundConfig_t> backgrounds;
};


class Parser : public LoggerSubject {

private:
    int fps;
    int loggerLevel;
    string mainFileName = MAIN_FILE_NAME;
    string backupFileName = BACKUP_FILE_NAME;
    Json::Value config;
    resolutionConfig_t resolutionConfig;
    vector<levelConfig_t> levelConfigVector;
    string pauseTexture;
    string startTexture;
    string shipTexture;
    string continueTexture;
    string enemyTexture;
    string nextLevelContinueTexture;

    vector<backgroundConfig_t> getBackgroundConfigDefault();

    void validateResolution();

    void loadResolutionInfo();

    void loadLoggerInfo();

    void loadResolution();

    void loadTextureInfo();

    void loadBackground(const Json::Value &levels, int i, levelConfig_t &level);

    void loadEnemies(const Json::Value &levels, int i, levelConfig_t &level);

    void loadLevelTexture(const Json::Value &levels, int i, levelConfig_t &level);

    void loadLevelsInfo();

    void loadLevelForIndex(const Json::Value &levels, int i);

public:
    //Constructor
    Parser();

    // Load config from json file.
    void loadConfig();

    // Default
    void loadEntireDefaultConfig();

    void loadDefaultMainFields();

    void loadDefaultLevelsConfig();

    // Getters

    Json::Value getConfig();

    resolutionConfig_t getResolutionConfig();

    vector<levelConfig_t> getLevelConfigVector();

    int getFps();

    int getLoggerLevel();

    string getPauseTexture();

    string getStartTexture();

    string getShipTexture();

    string getContinueTexture();

    string getEnemyTexture();

    void setNextLevelContinueTexture(string path);

    string getNextLevelContinueTexture();

    // Destructor
    ~Parser();

};

#endif

