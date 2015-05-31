#include "TrafficLightBase.h"

void TrafficLightBase::off() {
  transitionToState(STATE_OFF, nullptr, nullptr);
}
  
void TrafficLightBase::forceStop() {
  transitionToState(STATE_STOP, nullptr, nullptr);
}

void TrafficLightBase::stop(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  transitionToState(STATE_STOP, callbackObj, callbackFn);
}
  
void TrafficLightBase::go() {
  transitionToState(STATE_GO, nullptr, nullptr);
}
  
void TrafficLightBase::night() {
  transitionToState(STATE_NIGHT, nullptr, nullptr);
}


void TrafficLightBase::transitionToState(State state, void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  stopCurrentAnimation();
  m_currentState = state;
  isInTransition = true;
  switchState(callbackObj, callbackFn);
  if (callbackFn == nullptr) {
    transitionEnded();
  }
}



void TrafficLightBase::animationDone() {
  transitionEnded();
  Animatable::animationDone();
}

void TrafficLightBase::transitionEnded() {
  isInTransition = false;
}






