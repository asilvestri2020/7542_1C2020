#ifndef CONFIG_H_
#define CONFIG_H_

#include "../Model/Model.h"
#include "../Utils/LoggerSubject.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Config: public LoggerSubject
{
public:
    Config(Model* model, LoggerObserver* loggerObserver);
    virtual ~Config();
    void openJson();
    void readJson();
    void closeJson();

private:
    Model* model;
};

#endif
