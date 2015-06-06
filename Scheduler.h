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


public:

    Scheduler();
    virtual ~Scheduler();

    static void run();

    void startTimerPeriodically(uint32_t time_ms);
    void startTimerOnce(uint32_t time_ms);
    void clearTimer();

private:

    void startTimer(uint32_t time_ms);

    void link();
    void unlink();
    static Scheduler *getNodeBefore(Scheduler *node);

    void checkTimer(uint32_t current_time_ms);
    bool isReady(const uint32_t &current_time_ms);
    virtual void call() = 0;
};





class FunctionCallbackScheduler : public Scheduler {

public:
    typedef void (*CallbackFunction)(void);

private:
    CallbackFunction m_callbackFunction;

public:

    FunctionCallbackScheduler() :
            m_callbackFunction(nullptr) {};

    FunctionCallbackScheduler(CallbackFunction function) :
            m_callbackFunction(function) {};


    void runPeriodically(uint32_t time_ms, CallbackFunction function) {
        initCallback(function);
        startTimerPeriodically(time_ms);
    }
    void runOnce(uint32_t time_ms, CallbackFunction function) {
        initCallback(function);
        startTimerOnce(time_ms);
    }

protected:
    void call() { //override;
        if (m_callbackFunction != nullptr) m_callbackFunction();
    }

private:
    void initCallback(CallbackFunction function) {
        m_callbackFunction = function;
    }
};






template <class TCallbackObj>
class MethodCallbackScheduler : public Scheduler {

public:
    typedef void (TCallbackObj::*CallbackMethod)();

private:
    TCallbackObj& m_callbackObj;
    CallbackMethod m_callbackMethod;

public:

    MethodCallbackScheduler(TCallbackObj& callbackObj) :
            m_callbackObj(callbackObj), m_callbackMethod(nullptr) {};

    MethodCallbackScheduler(TCallbackObj& callbackObj, CallbackMethod method) :
            m_callbackObj(callbackObj), m_callbackMethod(method) {};


    void runPeriodically(uint32_t time_ms, CallbackMethod method) {
        initCallback(method);
        startTimerPeriodically(time_ms);
    }
    void runOnce(uint32_t time_ms, CallbackMethod method) {
        initCallback(method);
        startTimerOnce(time_ms);
    }

protected:
    void call() { //override;
        if (m_callbackMethod != nullptr) (m_callbackObj.*m_callbackMethod)();
    }

private:
    void initCallback(CallbackMethod method) {
        m_callbackMethod = method;
    }
};




#endif


