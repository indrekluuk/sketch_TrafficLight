#include "PedestrianTrafficLight.h"
#include "Constants.h"


PedestrianTrafficLight::PedestrianTrafficLight(int redLedPin, int greenLedPin) :
  m_animator(*this), m_redLight(redLedPin), m_greenLight(greenLedPin) 
{
  
}



void PedestrianTrafficLight::switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  m_animator.stopAnimation();
  
  switch (m_currentState) {
    default:
    case STATE_NIGHT: 
    case STATE_OFF: 
            allLightsOff();
            break;
    case STATE_STOP: 
            if (callbackFn == nullptr) {
              setRed();
            } else {
              runStopSequenceAnimation(callbackObj, callbackFn);
            }
            break;
    case STATE_GO: 
            setGreen();
            break;
  }
  
}



void PedestrianTrafficLight::allLightsOff() {
  m_redLight.off();
  m_greenLight.off();
}
  
void PedestrianTrafficLight::setRed() {
  m_redLight.on();
  m_greenLight.off();
}

void PedestrianTrafficLight::setGreen() {
  m_redLight.off();
  m_greenLight.on();
}

void PedestrianTrafficLight::setGreenPulsing() {
  m_redLight.off();
  m_greenLight.pulse();
}




void PedestrianTrafficLight::runStopSequenceAnimation(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  m_animator.startAnimation(ANIMATION_STOP_PEDESTRIANS, callbackObj, callbackFn, [](void* pAnimator) {
    Animator<PedestrianTrafficLight>::getThis(pAnimator)->setGreenPulsing();
    Animator<PedestrianTrafficLight>::wait(pAnimator, PEDESTRIAN_STOP_GREEN_BLINK_ms, [](void* pAnimator) {
      Animator<PedestrianTrafficLight>::getThis(pAnimator)->setRed();
      Animator<PedestrianTrafficLight>::getThis(pAnimator)->transitionEnded(); 
      Animator<PedestrianTrafficLight>::animationDone(pAnimator);
    });
  });
}




