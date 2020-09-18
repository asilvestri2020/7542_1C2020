#ifndef UTIL_TIMER_HEADER
#define UTIL_TIMER_HEADER

#include "SDL2/SDL_timer.h"
//The timer
class UtilTimer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    UtilTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
};

#endif