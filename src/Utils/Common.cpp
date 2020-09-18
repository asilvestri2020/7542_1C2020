#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <list>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>

using namespace std;

#include "../Utils/Common.h"
Common myUtil;

// Obtenemos la fecha con el siguiente formato -> YYYY-MM-DD.HH:mm:ss
string Common::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// Chequeamos que el archivo exista.
inline bool Common::fileExists (const std::string& name)
{
    ifstream f(name.c_str());
    if (f.good())
    {
        f.close();
        return true;
    }
    else
    {
        f.close();
        return false;
    }
}

// Un simple ToUpper para el String.
void stringToUpper(string &s)
{
   for(unsigned int l = 0; l < s.length(); l++)
  {
    s[l] = toupper(s[l]);
  }
}

void Common::createFile()
{
    // Definimos un nombre para el Log de manera que sea UNIVOCO.-
    string actualLogName = "./Logs/Log.txt";

    // Creamos e inicializamos nunestro nuevo archivos de log.
    std::ofstream outfile (actualLogName);
    //outfile.open(getLogFile());
    outfile << "Archivo de Log inicializado: " << myUtil.currentDateTime() << std::endl;
    outfile << std::endl;
    outfile.close();

    //Chequeamos que haya sido creado exitosamente.
    if(!fileExists(actualLogName))
    {
		    if (mkdir("./Logs",0777) == 0)
		    {
				std::ofstream file {"./Logs/Log.txt"};
				
				    if(!fileExists(actualLogName))
				    {
						perror(("No existe el archivo de Log que se intento inicializar."));
						exit(1);
					}
			}
			else
			{
				perror(("No se creo la carpeta, ni tampoco el archivo de log."));
				exit(1);
			}
    }
}

void Common::backupFile()
{
    string newFileName = "./Logs/Cerrado (" + myUtil.currentDateTime() + ") Log.txt";
    string oldFileName = "./Logs/Log.txt";
    int result = rename(oldFileName.c_str(), newFileName.c_str());
    if ( result == 0 )
        puts ( "Hemos sobreescrito el nombre del archivo." );
    else
        createFile();
}

// Get the horizontal and vertical screen sizes in pixel
void Common::getDesktopResolution(int& width, int& height)
{
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    width = s->width;
    height = s->height;
}

