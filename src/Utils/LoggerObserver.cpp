#include "../Utils/LoggerObserver.h"


LoggerObserver* LoggerObserver::instance = nullptr;

// Lifecycle
LoggerObserver::LoggerObserver() {
    this->utils = new Common();
    this->utils->backupFile();
    this->utils->createFile();
}

LoggerObserver::~LoggerObserver() {
    delete instance;
    instance = nullptr;
}

LoggerObserver* LoggerObserver::getInstance() {
    return (!instance) ?
        instance = new LoggerObserver():
        instance;
}

// Getters
int LoggerObserver::getLoggerLevel() {
    return this->level;
}

void LoggerObserver::updateLevel(int newLevel) {
    this->level = newLevel;
}

std::string LoggerObserver::getLogFile() {
    string fullPathString = "./Logs/Log.txt";
    return fullPathString;
}

// Line methods
void LoggerObserver::writeSingleLine(string line, string type, string environment) {
    ofstream log_file(getLogFile(), ios_base::out | ios_base::app );
    log_file << utils->currentDateTime() + " || " + type + " || " + environment + " || " << line << endl;
    log_file.close();
}

void LoggerObserver::writeDebugLine(std::string message, std::string environment) {
    if(getLoggerLevel() >= 3)
        writeSingleLine(message, "DEBUG", environment);
}

void LoggerObserver::writeInfoLine(std::string line, std::string environment) {
    if(getLoggerLevel() >= 2)
        writeSingleLine(line, "INFO", environment);
}

void LoggerObserver::writeErrorLine(std::string line, std::string environment) {
    if(getLoggerLevel() >= 1)
        writeSingleLine(line, "ERROR", environment);
}