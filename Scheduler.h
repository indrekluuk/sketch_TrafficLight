#ifndef Scheduler_h
#define Scheduler_h

#include "Callback.h"
#include <Arduino.h>


class Scheduler {

private:
    static Scheduler *s_firstNode;
    Scheduler *m_nextNode;

    uint32_t m_timer_ms;
    uint32_t m_previousTime_ms;
    bool m_isRunOnce;

    Callback* m_callback;


public:

    Scheduler();

    virtual ~Scheduler();

    static void run();



    void runPeriodically(uint32_t time_ms, Callback* callback);
    void runOnce(uint32_t time_ms, Callback* callback);
    void clearTimer();

private:

    void link();
    void unlink();
    static Scheduler *getNodeBefore(Scheduler *node);

    void initCallback(Callback* callback);
    void startTimer(uint32_t time_ms);

    void checkTimer(uint32_t current_time_ms);
    bool isReady(const uint32_t &current_time_ms);
    void call();

};


#endif


