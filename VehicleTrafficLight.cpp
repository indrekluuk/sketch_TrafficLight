#include "VehicleTrafficLight.h"
#include "Constants.h"


VehicleTrafficLight::VehicleTrafficLight(uint8_t redLedPin, uint8_t yellowLedPin, uint8_t greenLedPin) :
        m_animator(*this), m_redLight(redLedPin), m_yellowLight(yellowLedPin), m_greenLight(greenLedPin) {

}



void VehicleTrafficLight::off() {
    stopAnimation();
    allLightsOff();
}

void VehicleTrafficLight::forceStop() {
    stopAnimation();
    setRed();
}

void VehicleTrafficLight::stop(Callback& callback) {
    stopAnimation();
    runStopSequenceAnimation(callback);
}

void VehicleTrafficLight::forceGo() {
    stopAnimation();
    setGreen();
}

void VehicleTrafficLight::go(Callback& callback) {
    stopAnimation();
    runGoSequenceAnimation(callback);
}

void VehicleTrafficLight::night() {
    stopAnimation();
    setYellowPulsing();
}

void VehicleTrafficLight::stopAnimation() {
    m_animator.stopAnimation();
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





void VehicleTrafficLight::runStopSequenceAnimation(Callback& doneCallback) {
    m_animator.startAnimation(ANIMATION_STOP_TRAFFIC, &doneCallback, &VehicleTrafficLight::stopSequenceAnimationStep);
}

void VehicleTrafficLight::stopSequenceAnimationStep(uint8_t step) {
    switch (step) {
        case 1:
            setGreenPulsing();
            m_animator.wait(VECHILE_STOP_GREEN_BLINK_ms);
            break;
        case 2:
            setYellow();
            m_animator.wait(VECHILE_STOP_YELLOW_ms);
            break;
        case 3:
            setRed();
            break;
    }
}



void VehicleTrafficLight::runGoSequenceAnimation(Callback& doneCallback) {
    m_animator.startAnimation(ANIMATION_GO_TRAFFIC, &doneCallback, &VehicleTrafficLight::goSequenceAnimationStep);
}

void VehicleTrafficLight::goSequenceAnimationStep(uint8_t step) {
    switch (step) {
        case 1:
            setYellow();
            m_animator.wait(VECHILE_GO_YELLOW_ms);
            break;
        case 2:
            setGreen();
            break;
    }
}


