/*
 *
 * The MIT License (MIT)
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

#include "PedestrianTrafficLight.h"
#include "Constants.h"


PedestrianTrafficLight::PedestrianTrafficLight(uint8_t redLedPin, uint8_t greenLedPin) :
        m_animator(*this), m_redLight(redLedPin), m_greenLight(greenLedPin) {

}


void PedestrianTrafficLight::off() {
    stopAnimation();
    allLightsOff();
}

void PedestrianTrafficLight::forceStop() {
    stopAnimation();
    setRed();
}

void PedestrianTrafficLight::stop(Callback& done) {
    stopAnimation();
    runStopSequenceAnimation(done);
}

void PedestrianTrafficLight::forceGo() {
    stopAnimation();
    setGreen();
}

void PedestrianTrafficLight::go(Callback& done) {
    forceGo();
    done.call();
}

void PedestrianTrafficLight::night() {
    stopAnimation();
    allLightsOff();
}

void PedestrianTrafficLight::stopAnimation() {
    m_animator.stopAnimation();
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



void PedestrianTrafficLight::runStopSequenceAnimation(Callback& done) {
    m_animator.startAnimation(ANIMATION_STOP_PEDESTRIANS, &done, &PedestrianTrafficLight::stopSequenceAnimationStep);
}

void PedestrianTrafficLight::stopSequenceAnimationStep(uint8_t step) {
    switch (step) {
        case 1:
            setGreenPulsing();
            m_animator.nextWithDelay(PEDESTRIAN_STOP_GREEN_BLINK_ms);
            break;
        case 2:
            setRed();
            break;
    }
}

