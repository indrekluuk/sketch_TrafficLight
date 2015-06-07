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

#include "VehicleTrafficLight.h"
#include "Constants.h"


VehicleTrafficLight::VehicleTrafficLight(uint8_t redLedPin, uint8_t yellowLedPin, uint8_t greenLedPin) :
        m_sequencer(this), m_redLight(redLedPin), m_yellowLight(yellowLedPin), m_greenLight(greenLedPin) {

}



void VehicleTrafficLight::off() {
    stopAnimation();
    allLightsOff();
}

void VehicleTrafficLight::forceStop() {
    stopAnimation();
    setRed();
}

void VehicleTrafficLight::stop(Callback& done) {
    stopAnimation();
    runStopSequenceAnimation(done);
}

void VehicleTrafficLight::forceGo() {
    stopAnimation();
    setGreen();
}

void VehicleTrafficLight::go(Callback& done) {
    stopAnimation();
    runGoSequenceAnimation(done);
}

void VehicleTrafficLight::night() {
    stopAnimation();
    setYellowPulsing();
}

void VehicleTrafficLight::stopAnimation() {
    m_sequencer.stopSequence();
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





void VehicleTrafficLight::runStopSequenceAnimation(Callback& done) {
    m_sequencer.set(&VehicleTrafficLight::stopSequenceAnimationStep).startSequence(ANIMATION_STOP_TRAFFIC, &done);
}

void VehicleTrafficLight::stopSequenceAnimationStep(Sequencer & sequencer, uint8_t step) {
    switch (step) {
        case 1:
            setGreenPulsing();
            sequencer.nextWithDelay(VECHILE_STOP_GREEN_BLINK_ms);
            break;
        case 2:
            setYellow();
            sequencer.nextWithDelay(VECHILE_STOP_YELLOW_ms);
            break;
        case 3:
            setRed();
            break;
    }
}



void VehicleTrafficLight::runGoSequenceAnimation(Callback& done) {
    m_sequencer.set(&VehicleTrafficLight::goSequenceAnimationStep).startSequence(ANIMATION_GO_TRAFFIC, &done);
}

void VehicleTrafficLight::goSequenceAnimationStep(Sequencer & sequencer, uint8_t step) {
    switch (step) {
        case 1:
            setYellow();
            sequencer.nextWithDelay(VECHILE_GO_YELLOW_ms);
            break;
        case 2:
            setGreen();
            break;
    }
}


