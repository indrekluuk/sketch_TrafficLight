
#ifndef TrafficLightBase_h
#define TrafficLightBase_h


#include "Animatable.h"
#include "Scheduler.h"

class TrafficLightBase : public Animatable {
  
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

  void off();
  void forceStop();
  void stop(void* callbackObj, Scheduler::CallbackFn* callbackFn);
  void go();
  void night();


protected:
  virtual void switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) = 0;
  void callAnimationDone() override;
    
private:
  void transitionToState(State state, void* callbackObj, Scheduler::CallbackFn* callbackFn);
  void transitionEnded();
  
};



#endif


