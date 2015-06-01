#ifndef TrafficLightBase_h
#define TrafficLightBase_h


#include "Animator.h"


class TrafficLightBase {

public:


    virtual void off() = 0;

    virtual void forceStop() = 0;

    virtual void stop(Callback<> callback) = 0;

    virtual void forceGo() = 0;

    virtual void go(Callback<> callback) = 0;

    virtual void night() = 0;

    virtual void stopAnimation() = 0;

};


#endif


