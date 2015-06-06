/*
 *
 * Copyright (c) 2015 Indrek Luuk (indrek.luuk@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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

