
#ifndef TrafficLightBase_h
#define TrafficLightBase_h


#include "Animator.h"
#include "Scheduler.h"

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
  void stop(void* callbackObj, Scheduler::CallbackFn* callbackFn);
  void go();
  void night();


protected:
  virtual void switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) = 0;
  void transitionEnded();
  
private:
  void transitionToState(State state, void* callbackObj, Scheduler::CallbackFn* callbackFn);
  
  
};



#endif


