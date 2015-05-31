
#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"

template<class TAnimatedObj>
class Animator {
  
  static const int ANIMATION_STOPPED = 0;

  TAnimatedObj &m_animatedObj;

  Scheduler m_animationScheduler;
  int m_animationIdentifier = ANIMATION_STOPPED;
  Callback m_animationDoneCallback;
  
public:

  Animator(TAnimatedObj &animatedObj);
  
  void startAnimation(int animationIdentifier, Callback animationNextCallback);
  void startAnimation(int animationIdentifier, Callback doneCallback, Callback animationNextCallback);
  bool isAnimation(int animationIdentifier);
  void stopAnimation();
  
  static void wait(void *pAnimator, unsigned long time_ms, Callback animationNextCallback);
  static TAnimatedObj* getThis(void *pAnimator);
  static void animationDone(void *pAnimator);

private:
  void callDoneCallback();
  
};






template<class TAnimatedObj>
Animator<TAnimatedObj>::Animator(TAnimatedObj &animatedObj) :
        m_animationDoneCallback(nullptr, nullptr), m_animatedObj(animatedObj)
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
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier, Callback animationNextCallback) {
  startAnimation(animationIdentifier, Callback(), animationNextCallback);
}
  
template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier, Callback doneCallback, Callback animationNextCallback) {
  m_animationIdentifier = animationIdentifier;
  m_animationDoneCallback = doneCallback;
  animationNextCallback.call();
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::wait(void *pAnimator, unsigned long time_ms, Callback animationNextCallback) {
  ((Animator*)pAnimator)->m_animationScheduler.runOnce(time_ms, animationNextCallback);
}

template<class TAnimatedObj>
TAnimatedObj* Animator<TAnimatedObj>::getThis(void *pAnimator) {
    return &(((Animator*)pAnimator)->m_animatedObj);
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


