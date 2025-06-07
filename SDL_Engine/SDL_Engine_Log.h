#include "pch.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL3/SDL_log.h>

typedef enum 
{
    LOG_INFO = 0,
    LOG_ERROR,
    LOG_WARNING,
    LOG_DEBUG
} LogType;

void SDL_Engine_Log(LogType msg_type, const char* text)
{
    char am_pm[] = "AM";
    char timebuf[26];
    struct tm newtime;
    __time64_t long_time;
    errno_t err;

    // Get time as 64-bit integer.
    _time64(&long_time);
    // Convert to local time.
    err = _localtime64_s(&newtime, &long_time);
    if (err)
    {
        return;
    }
    if (newtime.tm_hour > 12)        // Set up extension.
        strcpy_s(am_pm, sizeof(am_pm), "PM");
    if (newtime.tm_hour > 12)        // Convert from 24-hour
        newtime.tm_hour -= 12;        // to 12-hour clock.
    if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.
        newtime.tm_hour = 12;

    // Convert to an ASCII representation.
    err = asctime_s(timebuf, 26, &newtime);
    if (err)
    {
        return;
    }

    switch (msg_type)
    {
        case LOG_INFO: SDL_Log("%.19s %s [INFO] : %s", timebuf, am_pm, text); break;
        case LOG_ERROR: SDL_Log("%.19s %s [ERROR]: %s", timebuf, am_pm, text); break;
        case LOG_WARNING: SDL_Log("%.19s %s [WARN] : %s", timebuf, am_pm, text); break;
        case LOG_DEBUG: SDL_Log("%.19s %s [DEBUG]: %s", timebuf, am_pm, text); break;
        default: break;
    }
    SDL_Log("\n");
}
