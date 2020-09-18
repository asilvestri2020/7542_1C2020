#ifndef MODEL_H
#define MODEL_H

#include "../Utils/LoggerSubject.h"
#include <string>

using namespace std;

class Model : public LoggerSubject
{

public:
    Model();
    virtual ~Model();
    virtual void update();

protected:

private:

};

#endif // MODEL_H
