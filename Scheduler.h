#ifndef Scheduler_h
#define Scheduler_h

#include "Callback.h"
#include <Arduino.h>


class Scheduler {

private:
    static Scheduler *s_firstNode;
    Scheduler *m_nextNode;

    unsigned long m_timer_ms;
    unsigned long m_previousTime_ms;
    bool m_isRunOnce;

    Callback* m_callback = nullptr;


public:

    Scheduler();

    virtual ~Scheduler();

    static void run();



    void runPeriodically(unsigned long time_ms, Callback* callback);
    void runOnce(unsigned long time_ms, Callback* callback);
    void clearTimer();

protected:

    void initCallback(Callback* callback);
    void startTimer(unsigned long time_ms);


    void call();


private:

    void link();

    void unlink();

    static Scheduler *getNodeBefore(Scheduler *node);

    bool isReady(const unsigned long &current_time_ms);

};


#endif


