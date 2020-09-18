#include "Parser.h"
#include <stdio.h>

Parser::Parser() {
	Attach();
};


void Parser::loadEntireDefaultConfig() {
	loadDefaultMainFields();
	loadDefaultLevelsConfig();
}

//carga los campos principales del objeto config
void Parser::loadDefaultMainFields() {
	this->resolutionConfig.height = DEFAULT_RESOLUTION_HEIGHT;
	this->resolutionConfig.width = DEFAULT_RESOLUTION_WIDTH;
	this->loggerLevel = DEFAULT_LOGGER_LEVEL;
	this->startTexture = DEFAULT_START_TEXTURE;
	this->shipTexture = DEFAULT_SHIP_TEXTURE;
	this->continueTexture = DEFAULT_CONTINUE_TEXTURE_2;
	this->pauseTexture = DEFAULT_PAUSE_TEXTURE;
	this->nextLevelContinueTexture = this->continueTexture;
	this->fps = DEFAULT_FPS;
}

void Parser::loadDefaultLevelsConfig() {
	NotifyError("No se puede cargar los niveles. Se cargaran los valores default.", GetEnviroment(__FILE__, __FUNCTION__));

	for (int i = 1; i < DEFAULT_LEVEL_NUMBER + 1; i++) {
		levelConfig_t actualLevel;
		actualLevel.bothDirections = true;
		actualLevel.number = i;
		actualLevel.continueTexture = DEFAULT_CONTINUE_TEXTURE_2;
		actualLevel.duration = DEFAULT_LEVEL_DURATION;
		actualLevel.numberOfEnemies = DEFAULT_ENEMIES_QTTY;
		//ES IRRELEVANTE QUE HAYAN MAS TIPOS DE ENEMIGOS TOTAL VAN A TENER LA MISMA TEXTURA...
		//vector<enemy_t> enemies;
		enemy_t enemy_1;
		enemy_1.type = to_string(i);
		enemy_1.path = DEFAULT_ENEMIY_TEXTURE;
		//enemies.push_back(enemy_1);
		actualLevel.enemies.push_back(enemy_1);
		//actualLevel.enemies[0].type=to_string(i);
		//actualLevel.enemies[0].path=DEFAULT_ENEMIY_TEXTURE;
		//ES IRRELEVANTE QUE HAYAN MAS FONDOS TOTAL VAN A TENER LA MISMA TEXTURA...
		actualLevel.backgrounds = this->getBackgroundConfigDefault();
		this->levelConfigVector.push_back(actualLevel);
	}
}

void Parser::loadResolutionInfo() {
	const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));

	NotifyInfo("Cargamos los valores para la resolucion.", enviroment);

	this->resolutionConfig.height = DEFAULT_RESOLUTION_HEIGHT;
	this->resolutionConfig.width = DEFAULT_RESOLUTION_WIDTH;
	if (config["resolution"] != Json::nullValue) {
		if ( config["resolution"].get("height", DEFAULT_RESOLUTION_HEIGHT).isInt()){
			this->resolutionConfig.height = config["resolution"].get("height", DEFAULT_RESOLUTION_HEIGHT).asInt();
		}

		if ( config["resolution"].get("width", DEFAULT_RESOLUTION_WIDTH).isInt()){
			this->resolutionConfig.width = config["resolution"].get("width", DEFAULT_RESOLUTION_WIDTH).asInt();
		}
		
	} else {
		NotifyError("No se pudo cargar las resoluciones del archivo. Se carga las default.	", enviroment);
	}
}

void Parser::loadLoggerInfo() {
	const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));

	NotifyInfo("Cargamos los valores para el logger.", enviroment);

	this->loggerLevel =  DEFAULT_LOGGER_LEVEL;
	if (config["loggerLevel"] == Json::nullValue) {
		NotifyError("No se pudo cargar el nivel de log, se cargara DEBUG por defecto (más inclusivo)", enviroment);
	}else if ( config.get("loggerLevel", DEFAULT_LOGGER_LEVEL).isInt()){
		
		int level = config.get("loggerLevel", DEFAULT_LOGGER_LEVEL).asInt();
		
		if( 0 < level && level < 4){
			this->loggerLevel = level;

		}else{
            NotifyError("Nivel de log invalido, se setea a nivel por defecto: 3",enviroment);
		}
		
	}else{
		NotifyError("No se pudo cargar el nivel de log, se cargara DEBUG por defecto (más inclusivo)", enviroment);
	}

	const std::string loggerLevelString = std::to_string(this->loggerLevel);
	NotifyInfo("Nivel de log cargado: " + loggerLevelString, enviroment);

}

void Parser::loadTextureInfo() {
	const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));

	Common util;
	this->startTexture = DEFAULT_START_TEXTURE;
	if (config.get("startTexture", DEFAULT_START_TEXTURE).isString()){
		this->startTexture = config.get("startTexture", DEFAULT_START_TEXTURE).asString();
	}
	
	if (!util.fileExists(this->startTexture))  //Este es el caso donde no se cargó la textura por defecto pero el path es ERRONEO.
		this->startTexture = DEFAULT_START_TEXTURE;

	if (this->startTexture.find("missing") != std::string::npos) //En caso de que en el path final tenga missing significa que es un ERROR contemplado.
		NotifyError("No existe la textura startTexture, usamos default: " + this->startTexture, enviroment);

	NotifyInfo("Tenemos como startTexture: " + this->startTexture, enviroment);

	this->pauseTexture = DEFAULT_PAUSE_TEXTURE;
	if (config.get("pauseTexture", DEFAULT_PAUSE_TEXTURE).isString()){
		this->pauseTexture = config.get("pauseTexture", DEFAULT_PAUSE_TEXTURE).asString();
	}
	
	if (!util.fileExists(this->pauseTexture))
		this->pauseTexture = DEFAULT_PAUSE_TEXTURE;

	if (this->pauseTexture.find("missing") != std::string::npos)
		NotifyError("No existe la textura pauseTexture, usamos default: " + this->pauseTexture, enviroment);

	NotifyInfo("Tenemos como pauseTexture: " + this->pauseTexture, enviroment);

	this->shipTexture = DEFAULT_SHIP_TEXTURE;
	if (config.get("shipTexture", DEFAULT_SHIP_TEXTURE).isString()){
		this->shipTexture = config.get("shipTexture", DEFAULT_SHIP_TEXTURE).asString();
	}
	
	if (!util.fileExists(this->shipTexture))
		this->shipTexture = DEFAULT_SHIP_TEXTURE;

	if (this->shipTexture.find("missing") != std::string::npos)
		NotifyError("No existe la textura shipTexture, usamos default: " + this->shipTexture, enviroment);

	NotifyInfo("Tenemos como shipTexture: " + this->shipTexture, enviroment);

	this->continueTexture = DEFAULT_CONTINUE_TEXTURE_2;
	if (config.get("continueTexture", DEFAULT_CONTINUE_TEXTURE_2).isString()){
		this->continueTexture = config.get("continueTexture", DEFAULT_CONTINUE_TEXTURE_2).asString();
	}
	
	if (!util.fileExists(this->continueTexture))
		this->continueTexture = DEFAULT_CONTINUE_TEXTURE_2;

	if (this->continueTexture.find("missing") != std::string::npos)
		NotifyError("No existe la textura continueTexture, usamos default: " + this->continueTexture, enviroment);

	NotifyInfo("Tenemos como continueTexture: " + this->continueTexture, enviroment);

	this->nextLevelContinueTexture = this->continueTexture;
}

void Parser::loadConfig() {
	std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
	std::fstream file;

	try {
		NotifyDebug("Comienzo parseo de archivo de configuracion", enviroment);
		file.open(this->mainFileName, std::ifstream::in);

		if (!file.is_open()) {
			NotifyError("No se pudo abrir el archivo config.json, se usara el archivo backup-config.json", enviroment);
			file.open(this->backupFileName, std::ifstream::in);
		}

		if (!file.is_open()) {
			NotifyError("No se pudo abrir el archivo de configuracion backup-json", enviroment);
			throw std::string("Throwing exception, could not open backup config.json file...");
		}

		Json::Reader reader;


		if (!reader.parse(file, config, true) || config.isNull() || !config.isObject()) {
			NotifyError(
					"No se pudo parsear el objeto config.json. No se respeta formato json y se cargara la configuracion entera por default.",
					enviroment);
			NotifyError(reader.getFormattedErrorMessages(), enviroment);
			loadEntireDefaultConfig();
		} else {
			//RESOLUCION
			loadResolutionInfo();

			//LOGGER
			loadLoggerInfo();

			//TEXTURAS PRINCIPALES DEL JUEGO
			loadTextureInfo();

			//FPS
			if (config.get("fps", DEFAULT_FPS).isInt()){
				this->fps = config.get("fps", DEFAULT_FPS).asInt();
			}else{
				this->fps = 60;
			}
			
			NotifyInfo("Tenemos como FPS el siguiente valor: " + to_string(this->fps), enviroment);

			//NIVELES
			loadLevelsInfo();

		}

		file.close();
		NotifyInfo("Fin parseo de archivo de configuracion", enviroment);

	}
	catch (const std::runtime_error &re) {
		file.close();
		NotifyError("Archivo de configuración CORRUPTO.", enviroment);
		NotifyError(re.what(), enviroment);
	}
	catch (const std::exception &ex) {
		file.close();
		NotifyError("Archivo de configuración CORRUPTO.", enviroment);
		NotifyError(ex.what(), enviroment);
	}
	catch (...) {
		file.close();
		NotifyError("Archivo de configuración CORRUPTO.", enviroment);
	}

}

void Parser::loadLevelsInfo() {
	const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
	const Json::Value levels = config["levels"];

	if (!levels.isNull()) {
		NotifyInfo("Niveles cargados desde el archivo de configuración.", enviroment);
		NotifyDebug("Cantidad de niveles: " + to_string(levels.size()), enviroment);
		for (int i = 0; i < levels.size(); ++i) {
			loadLevelForIndex(levels, i);
		}
	} else {
		loadDefaultLevelsConfig();
	}
}

void Parser::loadLevelForIndex(const Json::Value &levels, int i) {
   const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
   levelConfig_t level;

	if (levels[i].get("number", i).isInt()){
		level.number = levels[i].get("number", i).asInt();
	}else{
		level.number = i;
	}
   
   	NotifyInfo("Número de nivel: " + to_string(level.number), enviroment);

	if (levels[i].get("duration", DEFAULT_DURATION).isInt()){
		level.duration = levels[i].get("duration", DEFAULT_DURATION).asInt();
	}else{
		level.duration = DEFAULT_DURATION;
	}
   
   	NotifyInfo("Duración del nivel: " + to_string(level.duration), enviroment);

	if (levels[i].get("bothDirections", true).isInt()){
		level.bothDirections = levels[i].get("bothDirections", true).asBool();
	}else{
		level.bothDirections = true;
	}
   
   	loadLevelTexture(levels, i, level);
   	loadBackground(levels, i, level);
   	loadEnemies(levels, i, level);

	NotifyDebug("Agregamos el nivel al verctor de niveles.", enviroment);
	levelConfigVector.push_back(level);
}

void Parser::loadLevelTexture(const Json::Value &levels, int i, levelConfig_t &level) {
	const std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
	Common util;

	if (levels[i].get("continueTexture", DEFAULT_CONTINUE_TEXTURE_2).isString()){
		level.continueTexture = levels[i].get("continueTexture", DEFAULT_CONTINUE_TEXTURE_2).asString();
	}else{
		level.continueTexture = DEFAULT_CONTINUE_TEXTURE_2;
	}
	
	if (!util.fileExists(level.continueTexture))
		level.continueTexture = DEFAULT_CONTINUE_TEXTURE_2;
	if (level.continueTexture.find("missing") != std::string::npos)
		NotifyError("No existe la textura continueTexture, usamos default: " + level.continueTexture, enviroment);

	NotifyInfo("continueTexture para el nivel: " + level.continueTexture, enviroment);
}

void Parser::loadEnemies(const Json::Value &levels, int i, levelConfig_t &level) {
	std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
	Common util;

	if (levels[i].get("numberOfEnemies", DEFAULT_ENEMIES).isInt()){
		level.numberOfEnemies = levels[i].get("numberOfEnemies", DEFAULT_ENEMIES).asInt();
		NotifyInfo("Cantidad de enemigos del nivel: " + to_string(level.numberOfEnemies), enviroment);
	}else{
		level.numberOfEnemies = DEFAULT_ENEMIES;
		NotifyError("Cantidad de enemigos invalida. Seteado valor por defecto", enviroment);
	}

	
	const Json::Value enemies = levels[i]["enemies"];
	if (!enemies.isNull()) {
		for (int i = 0; i < enemies.size(); ++i) {
			enemy_t enemy;
			if ( enemies[i]["path"].isString()){
				enemy.path = enemies[i]["path"].asString();
			}else{
				enemy.path = DEFAULT_ENEMIY_TEXTURE;
			}
			
			if (!util.fileExists(enemy.path)) {
				NotifyError("No se pudo encontrar la imagen " + enemy.path + " del enemigo: " + enemy.type +
							". Se le coloca la imagen por default.", enviroment);
				enemy.path = DEFAULT_ENEMIY_TEXTURE;
			}
			NotifyInfo("Path del enemigo actual: " + to_string(i) + " >> " + enemy.path, enviroment);
			enemy.type = enemies[i]["type"].asString();
			if ( enemies[i]["type"].isString()){
				enemy.type = enemies[i]["type"].asString();
			}else{
				enemy.type = "enemy";
			}

			NotifyInfo("Type del enemigo actual: " + to_string(i) + " >> " + enemy.type, enviroment);
			level.enemies.push_back(enemy);
		}
	} else {
		//ES IRRELEVANTE QUE HAYAN MAS TIPOS DE ENEMIGOS TOTAL VAN A TENER LA MISMA TEXTURA DEFAULT...
		enemy_t defaultEnemy;
		defaultEnemy.type = to_string(i);
		defaultEnemy.path = DEFAULT_ENEMIY_TEXTURE;
		level.enemies.push_back(defaultEnemy);
		NotifyError("No se puede cargar los enemigos del nivel " + to_string(level.number) +
					"... Se cargaran los enemigos default.", GetEnviroment(__FILE__, __FUNCTION__));
	}
}

void Parser::loadBackground(const Json::Value &levels, int i, levelConfig_t &level) {
	std::string enviroment = string(__FILE__).append(" | ").append(string(__FUNCTION__));
	Common util;
	bool validBackground = true;
	int zeroBackground = 0;
	const Json::Value backgrounds = levels[i]["background"];
	if (!backgrounds.isNull()) {
		for (int i = 0; i < backgrounds.size(); ++i) {
			backgroundConfig_t background;
			if (backgrounds[i].get("path", DEFAULT_BACKGROUND_PATH).isString()){
				background.path = backgrounds[i].get("path", DEFAULT_BACKGROUND_PATH).asString();
			}else{
				background.path = DEFAULT_BACKGROUND_PATH;
			}

			NotifyInfo("Backgrounds del parallax (nivel actual): " + to_string(i) + " >> " + background.path,
					   enviroment);

			if (backgrounds[i].get("velocity", 0).isInt()){
				background.velocity = backgrounds[i].get("velocity", 0).asInt();
			}else{
				background.velocity = i;
			}

			NotifyInfo(
					"Velocidad del parallax (nivel actual): " + to_string(i) + " >> " + to_string(background.velocity),
					enviroment);
			if (background.velocity == 0) zeroBackground++;

			level.backgrounds.push_back(background);
			if (!util.fileExists(background.path) || zeroBackground > 1) {
				NotifyError("Los fondos y/o las velocidades del parallax son inconsistentes.", enviroment);
				validBackground = false;
			}
		}
		if (!validBackground) {
			NotifyError("Uno de las capas del fondo actual ha fallado al obtenerse, usamos el fondo por defecto.",
						enviroment);
			level.backgrounds = getBackgroundConfigDefault();
		}
	} else {
		NotifyError("Para el nivel actual no se ha definido un fondo y usamos uno por defecto.", enviroment);
		level.backgrounds = getBackgroundConfigDefault();
	}
};

vector<backgroundConfig_t> Parser::getBackgroundConfigDefault() {
	vector<backgroundConfig_t> backgrounds;
	backgroundConfig_t background1;
	backgroundConfig_t background2;
	backgroundConfig_t background3;
	backgroundConfig_t background4;
	backgroundConfig_t background5;
	backgroundConfig_t background6;
	background1.path = DEFAULT_BACKGROUND_PATH_16;
	background1.velocity = DEFAULT_BACKGROUND_VELOCITY_0;
	backgrounds.push_back(background1);

	background2.path = DEFAULT_BACKGROUND_PATH_15;
	background2.velocity = DEFAULT_BACKGROUND_VELOCITY_1;
	backgrounds.push_back(background2);

	background3.path = DEFAULT_BACKGROUND_PATH_14;
	background3.velocity = DEFAULT_BACKGROUND_VELOCITY_2;
	backgrounds.push_back(background3);

	background4.path = DEFAULT_BACKGROUND_PATH_13;
	background4.velocity = DEFAULT_BACKGROUND_VELOCITY_3;
	backgrounds.push_back(background4);

	background5.path = DEFAULT_BACKGROUND_PATH_12;
	background5.velocity = DEFAULT_BACKGROUND_VELOCITY_5;
	backgrounds.push_back(background5);

	background6.path = DEFAULT_BACKGROUND_PATH_11;
	background6.velocity = DEFAULT_BACKGROUND_VELOCITY_10;
	backgrounds.push_back(background6);
	return backgrounds;
}

Parser::~Parser() {

};

Json::Value Parser::getConfig() {
	return this->config;
};

resolutionConfig_t Parser::getResolutionConfig() {
	return this->resolutionConfig;
};


vector<levelConfig_t> Parser::getLevelConfigVector() {
	return this->levelConfigVector;
};

int Parser::getFps() {
	return this->fps;
}

string Parser::getPauseTexture() {
	return this->pauseTexture;
}

string Parser::getStartTexture() {
	return this->startTexture;
}

string Parser::getShipTexture() {
	return this->shipTexture;
}

string Parser::getContinueTexture() {
	return this->continueTexture;
}

string Parser::getEnemyTexture() {
	return this->enemyTexture;

}

int Parser::getLoggerLevel() {
	return this->loggerLevel;
}

void Parser::validateResolution() {
	if (resolutionConfig.height < DEFAULT_RESOLUTION_HEIGHT) {
		resolutionConfig.height = DEFAULT_RESOLUTION_HEIGHT;
		NotifyError("La resolucion minima es 800x600, se aplico el cambio de resolucion a la minima.",
					GetEnviroment(__FILE__, __FUNCTION__));
	}
	float correspondingWidth = ((this->resolutionConfig.height * 4) / 3);
	if ((int) floor(correspondingWidth) != this->resolutionConfig.width) {
		this->resolutionConfig.width = floor(correspondingWidth);
		NotifyError("No se respeta el formato 4:3, se corrije a la mas cercana: " +
					to_string((int) floor(correspondingWidth)) + "x" + to_string(this->resolutionConfig.height),
					GetEnviroment(__FILE__, __FUNCTION__));
	}
}

void Parser::setNextLevelContinueTexture(string path) {
	this->nextLevelContinueTexture = path;
}

string Parser::getNextLevelContinueTexture() {
	return this->nextLevelContinueTexture;

}