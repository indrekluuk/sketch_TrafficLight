#include "Animator.h"



Animator::Animator(void *pThis) {
  m_pThis = pThis;
}


  
bool Animator::isAnimation(int animationIdentifier) {
  return animationIdentifier == m_animatinIdentifier;
}


void Animator::stopAnimation() {
  m_animatinIdentifier = ANIMATION_STOPPED;
  m_animationScheduler.clearTimer();
}



void Animator::startAnimation(int animatinIdentifier, Scheduler::CallbackFn* animationNextCallbackFn) {
  startAnimation(animatinIdentifier, nullptr, nullptr, animationNextCallbackFn);
}
  
void Animator::startAnimation(int animatinIdentifier, void* doneCallbackObj, Scheduler::CallbackFn* doneCallbackFn, Scheduler::CallbackFn* animationNextCallbackFn) {
  m_animatinIdentifier = animatinIdentifier;
  m_animationDoneCallbackObj = doneCallbackObj;
  m_animationDoneCallbackFn = doneCallbackFn;
  animationNextCallbackFn(this);
}

void Animator::wait(void *pAnimator, unsigned long time_ms, Scheduler::CallbackFn* callbackFn) {
  ((Animator*)pAnimator)->m_animationScheduler.runOnce(time_ms, pAnimator, callbackFn);
}

void* Animator::getThis(void *pAnimator) {
    return ((Animator*)pAnimator)->m_pThis;
}

void Animator::animationDone(void *pAnimator) {
  ((Animator*)pAnimator)->stopAnimation();
  if (((Animator*)pAnimator)->m_animationDoneCallbackFn != nullptr) {
    ((Animator*)pAnimator)->m_animationDoneCallbackFn(((Animator*)pAnimator)->m_animationDoneCallbackObj);
  }
}


