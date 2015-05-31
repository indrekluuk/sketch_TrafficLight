#include "PedestrianTrafficLight.h"
#include "Constants.h"


PedestrianTrafficLight::PedestrianTrafficLight(int redLedPin, int greenLedPin) :
  m_redLight(redLedPin), m_greenLight(greenLedPin) 
{
  
}



void PedestrianTrafficLight::switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  
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
              initStopSequence(callbackObj, callbackFn);
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




void PedestrianTrafficLight::initStopSequence(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  initAnimationDoneCallback(callbackObj, callbackFn);
  
  setGreenPulsing();
  animate(PEDESTRIAN_STOP_GREEN_BLINK_ms, this, [](void* pThis) {
    ((PedestrianTrafficLight*)pThis)->setRed();
    ((PedestrianTrafficLight*)pThis)->animationDone(); 
  });
}
