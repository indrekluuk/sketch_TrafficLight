
#ifndef Animatable_h
#define Animatable_h


#include "Scheduler.h"



class Animatable {

  Scheduler m_animationScheduler;
  Scheduler::CallbackFn* m_animationDoneCallbackFn = nullptr;
  void* m_animationDoneCallbackObj = nullptr;
  
  
protected:
  
  void initAnimationDoneCallback(void* callbackObj, Scheduler::CallbackFn* callbackFn);
  virtual void animationDone();
  void stopCurrentAnimation();
  static void animate(unsigned long time_ms, void* pThis, Scheduler::CallbackFn* callbackFn);
  
};



#endif


