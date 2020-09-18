#include "../Model/Model.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>

Model::Model()
{

}

Model::~Model()
{

}

void Model::update()
{
    try
    {
        NotifyInfo("Inicia update", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        if(true)
        {
            NotifyInfo("Problema update", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        NotifyInfo("Termina update", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
    }
    catch(const std::runtime_error& re)
    {
        NotifyError("Error en Runtime: ", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        NotifyError(re.what(), string(__FILE__).append(" | ").append(string(__FUNCTION__)));
    }
    catch(const std::exception& ex)
    {
        NotifyError("Ha ocurrido un error: ", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        NotifyError(ex.what(), string(__FILE__).append(" | ").append(string(__FUNCTION__)));
    }
    catch(...)
    {
        NotifyError("Error desconocido que no se ha podido especificar.", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
    }
}