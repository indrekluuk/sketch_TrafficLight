#include "TrafficLightBase.h"


TrafficLightBase::TrafficLightBase()
{
}



void TrafficLightBase::off() {
  transitionToState(STATE_OFF, Callback());
}
  
void TrafficLightBase::forceStop() {
  transitionToState(STATE_STOP,  Callback());
}

void TrafficLightBase::stop(Callback callback) {
  transitionToState(STATE_STOP, callback);
}
  
void TrafficLightBase::go() {
  transitionToState(STATE_GO, Callback());
}
  
void TrafficLightBase::night() {
  transitionToState(STATE_NIGHT, Callback());
}


void TrafficLightBase::transitionToState(State state, Callback callback) {
  m_currentState = state;
  isInTransition = true;
  switchState(callback);
  if (!callback.isInitialized()) {
    transitionEnded();
  }
}



void TrafficLightBase::transitionEnded() {
  isInTransition = false;
}






