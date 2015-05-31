#include "Light.h"
#include <Arduino.h>


Light::Light(int pin) : m_ledPin(pin) {
  pinMode(m_ledPin, OUTPUT);
  off();

  m_scheduler.initCallback(Callback<Light>(this, Light::togglePulse));
}


void Light::on() {
  m_scheduler.clearTimer();
  setLedOn();
}
  
  
void Light::off() {
  m_scheduler.clearTimer();
  setLedOff();
}


void Light::pulse() {
  setLedOn();
  m_scheduler.runPeriodically(500);
}


void Light::togglePulse(Light *light) {
  light->toggle();
}


void Light::toggle() {
  if (m_isLedOn) {
    setLedOff();
  } else {
    setLedOn();
  }
}


void Light::setLedOn() {
  m_isLedOn = true;
  digitalWrite(m_ledPin, HIGH);
}
    
void Light::setLedOff() {
  m_isLedOn = false;
  digitalWrite(m_ledPin, LOW);
}

