#include "Animatable.h"





void Animatable::initAnimationDoneCallback(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  m_animationDoneCallbackFn = callbackFn;
  m_animationDoneCallbackObj = callbackObj;
}

void Animatable::animationDone() {
  if (m_animationDoneCallbackFn != nullptr) {
    m_animationDoneCallbackFn(m_animationDoneCallbackObj);
  }
}


void Animatable::stopCurrentAnimation() {
  m_animationScheduler.clearTimer();
}



void Animatable::animate(unsigned long time_ms, void* pThis, Scheduler::CallbackFn* callbackFn) {
  ((Animatable*)pThis)->m_animationScheduler.runOnce(time_ms, pThis, callbackFn);
}

