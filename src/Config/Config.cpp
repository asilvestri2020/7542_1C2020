#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../Config/Config.h"

Config::Config(Model* model, LoggerObserver* loggerObserver)
{
    this->Attach(loggerObserver);
    try
    {
        NotifyInfo("Efectuamos tal tarea de manera exitosa...", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        this->openJson();
        this->closeJson();
        if(true)
        {
            NotifyInfo("Advertencia ha ocurrido lo siguiente...", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        this->closeJson();
        NotifyInfo("Efectuamos tal tarea de manera exitosa...", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
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

Config::~Config()
{
    this->closeJson();
}

void Config::openJson()
{
    try
    {
        NotifyInfo("Inicia openJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        if(true)
        {
            NotifyInfo("Problema openJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        NotifyInfo("Termina openJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
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

void Config::readJson()
{
    try
    {
        NotifyInfo("Inicia readJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        if(true)
        {
            NotifyInfo("Problema readJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        NotifyInfo("Termina readJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
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

void Config::closeJson()
{
    try
    {
        NotifyInfo("Inicia closeJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        if(true)
        {
            NotifyInfo("Problema closeJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
        }
        NotifyInfo("Termina closeJson", string(__FILE__).append(" | ").append(string(__FUNCTION__)));
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