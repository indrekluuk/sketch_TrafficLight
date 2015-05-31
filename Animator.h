
#ifndef Animator_h
#define Animator_h


#include "SchedulerTemplate.h"

template<class TAnimatedObj>
class Animator {

  typedef void(AnimatorCallbackFn)(Animator*);

  static const int ANIMATION_STOPPED = 0;


  TAnimatedObj &m_animatedObj;
  SchedulerTemplate<Animator> m_animationScheduler;
  int m_animationIdentifier = ANIMATION_STOPPED;
  Callback<> m_animationDoneCallback;
  Callback<Animator> delayedResponseCallback;
  
public:

  Animator(TAnimatedObj &animatedObj);

  void startAnimation(int animationIdentifier, AnimatorCallbackFn* animationNextCallbackFn);
  void startAnimation(int animationIdentifier, Callback<> doneCallback, AnimatorCallbackFn* animationNextCallbackFn);
  bool isAnimation(int animationIdentifier);
  void stopAnimation();

  void wait(unsigned long time_ms, AnimatorCallbackFn* animationNextCallbackFn) ;
  Callback<> waitForResponse(AnimatorCallbackFn* animationNextCallbackFn);
  static void callDelayedResponse(void* pDelayedResponseCallback);

  TAnimatedObj* getThis();

  static void animationDone(void *pAnimator);

private:
  void callDoneCallback();
  
};






template<class TAnimatedObj>
Animator<TAnimatedObj>::Animator(TAnimatedObj &animatedObj) :
        m_animationDoneCallback(), m_animatedObj(animatedObj)
{
}


template<class TAnimatedObj>
bool Animator<TAnimatedObj>::isAnimation(int animationIdentifier) {
  return animationIdentifier == m_animationIdentifier;
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::stopAnimation() {
  m_animationIdentifier = ANIMATION_STOPPED;
  m_animationScheduler.clearTimer();
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier,AnimatorCallbackFn* animationNextCallbackFn) {
  startAnimation(animationIdentifier, Callback<>(), animationNextCallbackFn);
}
  
template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier, Callback<> doneCallback, AnimatorCallbackFn* animationNextCallbackFn) {
  m_animationIdentifier = animationIdentifier;
  m_animationDoneCallback = doneCallback;
  Callback<Animator>(this, animationNextCallbackFn).call();
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::wait(unsigned long time_ms, AnimatorCallbackFn* animationNextCallbackFn) {
  m_animationScheduler.runOnceWithCallback(time_ms, Callback<Animator>(this, animationNextCallbackFn));
}


template<class TAnimatedObj>
Callback<> Animator<TAnimatedObj>::waitForResponse(AnimatorCallbackFn* animationNextCallbackFn) {
  delayedResponseCallback.reinit(this, animationNextCallbackFn);
  return Callback<>(&delayedResponseCallback, callDelayedResponse);
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::callDelayedResponse(void* pDelayedResponseCallback) {
  ((Callback<Animator>*)pDelayedResponseCallback)->call();
}



template<class TAnimatedObj>
TAnimatedObj* Animator<TAnimatedObj>::getThis() {
  return &m_animatedObj;
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::animationDone(void *pAnimator) {
  ((Animator*)pAnimator)->stopAnimation();
  ((Animator*)pAnimator)->callDoneCallback();
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::callDoneCallback() {
  m_animationDoneCallback.call();
}
  


#endif


