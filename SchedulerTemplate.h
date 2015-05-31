//
// Created by indrek on 31.05.2015.
//

#ifndef SKETCH_TRAFFICLIGHT_SCHEDULERTEMPLATE_H
#define SKETCH_TRAFFICLIGHT_SCHEDULERTEMPLATE_H


#include "Scheduler.h"


template<class TCallbackObject = void *>
class SchedulerTemplate : public Scheduler {

    Callback<TCallbackObject> m_callback;


public:

    void runPeriodicallyWithCallback(unsigned long time_ms, Callback<TCallbackObject> callback);

    void runOnceWithCallback(unsigned long time_ms, Callback<TCallbackObject> callback);

    void initCallback(Callback<TCallbackObject> callback);


protected:
    void call();

};


template<class TCallbackObject>
void SchedulerTemplate<TCallbackObject>::runPeriodicallyWithCallback(unsigned long time_ms,
                                                                     Callback<TCallbackObject> callback) {
    initCallback(callback);
    runPeriodically(time_ms);
}


template<class TCallbackObject>
void SchedulerTemplate<TCallbackObject>::runOnceWithCallback(unsigned long time_ms,
                                                             Callback<TCallbackObject> callback) {
    initCallback(callback);
    runOnce(time_ms);
}


template<class TCallbackObject>
void SchedulerTemplate<TCallbackObject>::initCallback(Callback<TCallbackObject> callback) {
    m_callback = callback;
}


template<class TCallbackObject>
void SchedulerTemplate<TCallbackObject>::call() {
    m_callback.call();
}


#endif //SKETCH_TRAFFICLIGHT_SCHEDULERTEMPLATE_H
