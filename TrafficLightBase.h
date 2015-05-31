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

    void go();

    void night();


protected:
    virtual void switchState(Callback<> callback) = 0;

    void transitionEnded();

private:
    void transitionToState(State state, Callback<> callback);


};


#endif


