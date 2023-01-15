#ifndef JUDD_TIME_H
#define JUDD_TIME_H
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux
#include <time.h>
#include <math.h>
#include <errno.h>    
#endif
long judd_get_time();
void judd_delay(long ms);
#endif
#ifdef JUDD_TIME_IMPL
long judd_get_time()
{
    long ms; 
#ifdef __linux__
    time_t s;
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    ms = round(spec.tv_nsec * 100);
#endif
#ifdef _WIN32
    SYSTEMTIME st;
    GetSystemTime(&st);
    ms = st.wHour*1000*60*60 + st.wMinute*1000*60 + st.wSecond*1000 + st.wMilliseconds
#endif
    return ms;
}
void judd_delay(long ms){
#ifdef __linux
    struct timespec ts;
    int res;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
#endif
#ifdef _WIN32
    Sleep(ms);
#endif
}
#endif