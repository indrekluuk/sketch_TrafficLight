#include "Light.h"
#include "Constants.h"
#include <Arduino.h>



Light::Light(int pin) :
        m_ledPin(pin),
        m_togglePulseCallback(*this, Light::toggle),
        m_isLedOn(false)
{
    pinMode(m_ledPin, OUTPUT);
    off();
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
    m_scheduler.runPeriodically(LIGHT_PULSE_TOGGLE_PERIOD_ms, &m_togglePulseCallback);
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

