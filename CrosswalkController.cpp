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

#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(uint8_t red1, uint8_t yellow1, uint8_t green1, uint8_t red2, uint8_t green2) :
        m_sequencer(*this),
        m_vehicleTrafficLight(red1, yellow1, green1),
        m_pedestrianTrafficLight(red2, green2)
{
}


void CrosswalkController::off() {
    stopAnimation();
    m_vehicleTrafficLight.off();
    m_pedestrianTrafficLight.off();
}

void CrosswalkController::on() {
    stopAnimation();
    m_vehicleTrafficLight.forceGo();
    m_pedestrianTrafficLight.forceStop();
}

void CrosswalkController::buttonPressed() {
    if (!m_sequencer.isSequenceRunning(ANIMATION_BUTTON_PRESSED)) {
        stopAnimation();
        runPedestrianButtonCycleAnimation();
    }
}

void CrosswalkController::night() {
    stopAnimation();
    m_vehicleTrafficLight.night();
    m_pedestrianTrafficLight.night();
}




void CrosswalkController::stopAnimation() {
    m_sequencer.stopSequence();
    m_vehicleTrafficLight.stopAnimation();
    m_pedestrianTrafficLight.stopAnimation();
}






void CrosswalkController::runPedestrianButtonCycleAnimation() {
    m_sequencer.startSequence(ANIMATION_BUTTON_PRESSED, &CrosswalkController::pedestrianButtonCycleAnimationStep);
}

void CrosswalkController::pedestrianButtonCycleAnimationStep(Sequencer & sequencer, uint8_t step) {
    switch (step) {
        case 1:
            m_pedestrianTrafficLight.forceStop();
            m_vehicleTrafficLight.stop(sequencer.nextWhenDone());
            break;
        case 2:
            sequencer.nextWithDelay(PEDESTRIAN_GO_DELAY_ms);
            break;
        case 3:
            m_pedestrianTrafficLight.go(sequencer.nextWhenDone());
            break;
        case 4:
            sequencer.nextWithDelay(PEDESTRIAN_GO_GREEN_ms);
            break;
        case 5:
            m_pedestrianTrafficLight.stop(sequencer.nextWhenDone());
            break;
        case 6:
            sequencer.nextWithDelay(VECHILE_GO_DELAY_ms);
            break;
        case 7:
            m_vehicleTrafficLight.go(sequencer.nextWhenDone());
            break;
        case 8:
            break;
    }
}

