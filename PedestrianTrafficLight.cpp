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

