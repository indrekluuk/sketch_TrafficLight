/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Indrek Luuk (indrek.luuk@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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

    void runPeriodically(uint32_t time_ms);
    void runOnce(uint32_t time_ms);
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


    virtual void callPeriodically(uint32_t time_ms, CallbackFunction function) {
        initCallback(function);
        Scheduler::runPeriodically(time_ms);
    }
    virtual void callOnce(uint32_t time_ms, CallbackFunction function) {
        initCallback(function);
        Scheduler::runOnce(time_ms);
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


    void callPeriodically(uint32_t time_ms, CallbackMethod method) {
        initCallback(method);
        Scheduler::runPeriodically(time_ms);
    }
    void callOnce(uint32_t time_ms, CallbackMethod method) {
        initCallback(method);
        Scheduler::runOnce(time_ms);
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


