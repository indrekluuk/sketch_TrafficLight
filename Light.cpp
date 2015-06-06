#include "Light.h"
#include "Constants.h"
#include <Arduino.h>



Light::Light(uint8_t pin) :
        m_ledPin(pin),
        m_pulseScheduler(*this, &Light::toggle),
        m_isLedOn(false)
{
    pinMode(m_ledPin, OUTPUT);
    off();
}


void Light::on() {
    m_pulseScheduler.clearTimer();
    setLedOn();
}


void Light::off() {
    m_pulseScheduler.clearTimer();
    setLedOff();
}


void Light::pulse() {
    toggle();
    m_pulseScheduler.startTimerPeriodically(LIGHT_PULSE_TOGGLE_PERIOD_ms);
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

