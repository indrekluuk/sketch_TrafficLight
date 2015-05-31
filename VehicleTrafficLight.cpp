#include "VehicleTrafficLight.h"
#include "Constants.h"


VehicleTrafficLight::VehicleTrafficLight(int redLedPin, int yellowLedPin, int greenLedPin) :
  m_redLight(redLedPin), m_yellowLight(yellowLedPin), m_greenLight(greenLedPin) 
{
  
}


  
void VehicleTrafficLight::switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  
  switch (m_currentState) {
    default:
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
    case STATE_NIGHT: 
            setYellowPulsing();
            break;
  }
}



void VehicleTrafficLight::allLightsOff() {
  m_redLight.off();
  m_yellowLight.off();
  m_greenLight.off();
}
  
void VehicleTrafficLight::setRed() {
  m_redLight.on();
  m_yellowLight.off();
  m_greenLight.off();
}

void VehicleTrafficLight::setGreen() {
  m_redLight.off();
  m_yellowLight.off();
  m_greenLight.on();
}

void VehicleTrafficLight::setGreenPulsing() {
  m_redLight.off();
  m_yellowLight.off();
  m_greenLight.pulse();
}

void VehicleTrafficLight::setYellow() {
  m_redLight.off();
  m_yellowLight.on();
  m_greenLight.off();
}

void VehicleTrafficLight::setYellowPulsing() {
  m_redLight.off();
  m_yellowLight.pulse();
  m_greenLight.off();
}



void VehicleTrafficLight::initStopSequence(void* callbackObj, Scheduler::CallbackFn* callbackFn) {
  initAnimationDoneCallback(callbackObj, callbackFn);
  
  setGreenPulsing();
  animate(VECHILE_STOP_GREEN_BLINK_ms, this, [](void* pThis) {
    ((VehicleTrafficLight*)pThis)->setYellow();
    animate(VECHILE_STOP_YELLOW_ms, pThis, [](void* pThis) {
      ((VehicleTrafficLight*)pThis)->setRed();
      ((VehicleTrafficLight*)pThis)->animationDone();      
    });
  });
}









