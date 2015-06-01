#ifndef TrafficLightBase_h
#define TrafficLightBase_h


#include "Animator.h"


class TrafficLightBase {

protected:
    enum State {
        STATE_OFF,
        STATE_STOP,
        STATE_GO,
        STATE_NIGHT
    };

    State m_currentState = STATE_OFF;
    bool isInTransition = false;

public:


    TrafficLightBase();

    void off();

    void forceStop();

    void stop(Callback<> callback);

    void forceGo();

    void go(Callback<> callback);

    void night();


    virtual void stopAnimation() = 0;


protected:
    virtual void switchState(Callback<> callback) = 0;

    void transitionEnded();

private:
    void transitionToState(State state, Callback<> callback);


};


#endif


