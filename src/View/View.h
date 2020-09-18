#ifndef VIEW_H
#define VIEW_H

#include "../Model/Model.h"
#include "../Utils/LoggerSubject.h"
#include <string>

using namespace std;

class View : public LoggerSubject
{
public:
    View(Model* model);
    virtual ~View();
    void render();
    void loadMedia();
    void close();

private:
    Model* model;
};

#endif // VIEW_H
