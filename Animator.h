
#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"

template<class TAnimaObj>
class Animator {
  
  static const int ANIMATION_STOPPED = 0;

  TAnimaObj &m_animaObj;

  Scheduler m_animationScheduler;
  int m_animatinIdentifier = ANIMATION_STOPPED;
  Scheduler::CallbackFn* m_animationDoneCallbackFn = nullptr;
  void* m_animationDoneCallbackObj = nullptr;
  
public:

  Animator(TAnimaObj &animaObj);
  
  void startAnimation(int animatinIdentifier, Scheduler::CallbackFn* animationNextCallbackFn);
  void startAnimation(int animatinIdentifier, void* doneCallbackObj, Scheduler::CallbackFn* doneCallbackFn, Scheduler::CallbackFn* animationNextCallbackFn);
  bool isAnimation(int animationIdentifier);
  void stopAnimation();
  
  static void wait(void *pAnimator, unsigned long time_ms, Scheduler::CallbackFn* animationNextCallbackFn);
  static TAnimaObj* getThis(void *pAnimator);
  static void animationDone(void *pAnimator);

private:
  void callDoneCallback();
  
};






template<class TAnimaObj>
Animator<TAnimaObj>::Animator(TAnimaObj &animaObj) :
  m_animaObj(animaObj)
{
}


template<class TAnimaObj>
bool Animator<TAnimaObj>::isAnimation(int animationIdentifier) {
  return animationIdentifier == m_animatinIdentifier;
}

template<class TAnimaObj>
void Animator<TAnimaObj>::stopAnimation() {
  m_animatinIdentifier = ANIMATION_STOPPED;
  m_animationScheduler.clearTimer();
}


template<class TAnimaObj>
void Animator<TAnimaObj>::startAnimation(int animatinIdentifier, Scheduler::CallbackFn* animationNextCallbackFn) {
  startAnimation(animatinIdentifier, nullptr, nullptr, animationNextCallbackFn);
}
  
template<class TAnimaObj>
void Animator<TAnimaObj>::startAnimation(int animatinIdentifier, void* doneCallbackObj, Scheduler::CallbackFn* doneCallbackFn, Scheduler::CallbackFn* animationNextCallbackFn) {
  m_animatinIdentifier = animatinIdentifier;
  m_animationDoneCallbackObj = doneCallbackObj;
  m_animationDoneCallbackFn = doneCallbackFn;
  animationNextCallbackFn(this);
}

template<class TAnimaObj>
void Animator<TAnimaObj>::wait(void *pAnimator, unsigned long time_ms, Scheduler::CallbackFn* callbackFn) {
  ((Animator*)pAnimator)->m_animationScheduler.runOnce(time_ms, pAnimator, callbackFn);
}

template<class TAnimaObj>
TAnimaObj* Animator<TAnimaObj>::getThis(void *pAnimator) {
    return &(((Animator*)pAnimator)->m_animaObj);
}

template<class TAnimaObj>
void Animator<TAnimaObj>::animationDone(void *pAnimator) {
  ((Animator*)pAnimator)->stopAnimation();
  ((Animator*)pAnimator)->callDoneCallback();
}

template<class TAnimaObj>
void Animator<TAnimaObj>::callDoneCallback() {
  if (m_animationDoneCallbackFn != nullptr) {
    m_animationDoneCallbackFn(m_animationDoneCallbackObj);
  }  
}
  


#endif


