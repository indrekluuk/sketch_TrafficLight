#include "Light.h"
#import <Arduino.h>


Light::Light(int pin) : m_ledPin(pin) {
  pinMode(m_ledPin, OUTPUT);
  off();
  
  scheduler.initCallback(this, Light::togglePulse);
}


void Light::on() {
  scheduler.clearTimer();
  setLedOn();
}
  
  
void Light::off() {
  scheduler.clearTimer();
  setLedOff();
}


void Light::pulse() {
  setLedOn();
  scheduler.runPeriodically(500);
}


void Light::togglePulse(void *light) {
  ((Light*)light)->toggle();
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

