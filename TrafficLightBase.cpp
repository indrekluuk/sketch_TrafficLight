#include "TrafficLightBase.h"


TrafficLightBase::TrafficLightBase() {
}


void TrafficLightBase::off() {
    transitionToState(STATE_OFF, Callback<>());
}

void TrafficLightBase::forceStop() {
    transitionToState(STATE_STOP, Callback<>());
}

void TrafficLightBase::stop(Callback<> callback) {
    transitionToState(STATE_STOP, callback);
}

void TrafficLightBase::forceGo() {
    transitionToState(STATE_GO, Callback<>());
}

void TrafficLightBase::go(Callback<> callback) {
    transitionToState(STATE_GO, callback);
}

void TrafficLightBase::night() {
    transitionToState(STATE_NIGHT, Callback<>());
}


void TrafficLightBase::transitionToState(State state, Callback<> callback) {
    m_currentState = state;
    isInTransition = true;
    switchState(callback);
}


void TrafficLightBase::transitionEnded() {
    isInTransition = false;
}






