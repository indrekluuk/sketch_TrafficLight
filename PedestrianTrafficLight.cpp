#include "PedestrianTrafficLight.h"
#include "Constants.h"


PedestrianTrafficLight::PedestrianTrafficLight(int redLedPin, int greenLedPin) :
  m_animator(*this), m_redLight(redLedPin), m_greenLight(greenLedPin) 
{
  
}



void PedestrianTrafficLight::switchState(Callback<> callback) {
  m_animator.stopAnimation();
  
  switch (m_currentState) {
    default:
    case STATE_NIGHT: 
    case STATE_OFF: 
            allLightsOff();
            break;
    case STATE_STOP: 
            if (callback.isInitialized()) {
                runStopSequenceAnimation(callback);
            } else {
                setRed();
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




void PedestrianTrafficLight::runStopSequenceAnimation(Callback<> doneCallback) {
  m_animator.startAnimation(ANIMATION_STOP_PEDESTRIANS, doneCallback, [](Animator<PedestrianTrafficLight>* pAnimator) {
      pAnimator->getThis()->setGreenPulsing();
      pAnimator->wait(PEDESTRIAN_STOP_GREEN_BLINK_ms, [](Animator<PedestrianTrafficLight>* pAnimator) {
          pAnimator->getThis()->setRed();
          pAnimator->getThis()->transitionEnded();
          pAnimator->animationDone(pAnimator);
      });
  });
}




