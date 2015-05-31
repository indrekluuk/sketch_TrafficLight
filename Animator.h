
#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"



class Animator {
  
  static const int ANIMATION_STOPPED = 0;

  void *m_pThis;

  Scheduler m_animationScheduler;
  int m_animatinIdentifier = ANIMATION_STOPPED;
  Scheduler::CallbackFn* m_animationDoneCallbackFn = nullptr;
  void* m_animationDoneCallbackObj = nullptr;
  
public:

  Animator(void *pThis);
  
  void startAnimation(int animatinIdentifier, Scheduler::CallbackFn* animationNextCallbackFn);
  void startAnimation(int animatinIdentifier, void* doneCallbackObj, Scheduler::CallbackFn* doneCallbackFn, Scheduler::CallbackFn* animationNextCallbackFn);
  bool isAnimation(int animationIdentifier);
  void stopAnimation();
  
  static void wait(void *pAnimator, unsigned long time_ms, Scheduler::CallbackFn* animationNextCallbackFn);
  static void* getThis(void *pAnimator);
  static void animationDone(void *pAnimator);

  
};



#endif


