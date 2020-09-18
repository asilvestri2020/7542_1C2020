#ifndef LoggerSubject_H
#define LoggerSubject_H

#include <vector>
#include <list>
#include <algorithm>
#include "../Utils/LoggerObserver.h"

class LoggerSubject {
	private:
		std::vector < LoggerObserver * > list;

	public:
		void Attach(LoggerObserver * logger);
        void Attach();
        void Detach(LoggerObserver * logger);
        void Detach();
        void NotifyInfo(std::string message, std::string environment);
        void NotifyDebug(std::string message, std::string environment);
        void NotifyError(std::string message, std::string environment);
        void NotifyLevel(int newLevel);
        std::string GetEnviroment(const char * file, const char * function);
};

#endif // LoggerSubject_H
