#include "../Utils/LoggerSubject.h"

void LoggerSubject::Attach(LoggerObserver* logger) {
    list.push_back(logger);
}

void LoggerSubject::Attach() {
        // Atach to logger observer
    LoggerObserver* observer ;
	observer = observer->getInstance();
	this->Attach(observer);
}

void LoggerSubject::Detach(LoggerObserver* logger) {
    list.erase(std::remove(list.begin(), list.end(), logger), list.end());
}

void LoggerSubject::Detach() {
    // Detach to logger observer
    LoggerObserver* observer ;
	observer = observer->getInstance();
	this->Detach(observer);
}

void LoggerSubject::NotifyInfo(std::string message, std::string environment) {
    for(vector<LoggerObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
        if(*iter != 0)
            (*iter)->writeInfoLine(message, environment);
    }
}

void LoggerSubject::NotifyError(std::string message, std::string environment) {
    for(vector<LoggerObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
        if(*iter != 0)
            (*iter)->writeErrorLine(message, environment);
    }
}

void LoggerSubject::NotifyDebug(std::string message, std::string environment) {
    for(vector<LoggerObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
        if(*iter != 0)
            (*iter)->writeDebugLine(message, environment);
    }
}

void LoggerSubject::NotifyLevel(int newLevel) {
    for(vector<LoggerObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
        if(*iter != 0)
            (*iter)->updateLevel(newLevel);
    }
}

std::string LoggerSubject::GetEnviroment(const char * file, const char * function) {
    return string(file).append(" | ").append(string(function));
}