
#include <SDL2/SDL.h>
#include "../View/View.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

View::View(Model* model)
{
    this->model = model;
    this->loadMedia();
}

View::~View()
{
    this->close();
}

void View::render()
{
}

void View::loadMedia()
{
        NotifyInfo("Inicia loadMedia", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        if(true)
        {
            NotifyInfo("Problema loadMedia", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        NotifyInfo("Termina loadMedia", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
}

void View::close()
{
}
