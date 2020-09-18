#ifndef LoggerObserver_H
#define LoggerObserver_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

#include "../Utils/Common.h"

class LoggerObserver {
	public:
		// GetInstance for singleton
		static LoggerObserver * getInstance();

		int getLoggerLevel();
		void updateLevel(int newLevel);

		// Write lines
		void writeInfoLine(std::string message, std::string environment);
		void writeErrorLine(std::string message, std::string environment);
		void writeDebugLine(std::string message, std::string environment);

	private:

		// Private pointer to instance
		static LoggerObserver * instance;

		//Level log
		int level;

		//Utils
		Common * utils;

		// Constructor
		LoggerObserver();

		// Destructor
		virtual~LoggerObserver();

		std::string getLogFile();

		void writeSingleLine(std::string line, std::string type, std::string environment);

};

#endif // LoggerObserver_H