#include "VehicleTrafficLight.h"
#include "Constants.h"


VehicleTrafficLight::VehicleTrafficLight(int redLedPin, int yellowLedPin, int greenLedPin) :
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
    m_animator.startAnimation(ANIMATION_STOP_TRAFFIC, &doneCallback, VehicleTrafficLight::animate_stopSequence_1);
}

void VehicleTrafficLight::animate_stopSequence_1() {
    setGreenPulsing();
    m_animator.wait(VECHILE_STOP_GREEN_BLINK_ms, animate_stopSequence_2);
}

void VehicleTrafficLight::animate_stopSequence_2() {
    setYellow();
    m_animator.wait(VECHILE_STOP_YELLOW_ms, animate_stopSequence_3);
}

void VehicleTrafficLight::animate_stopSequence_3() {
    setRed();
    m_animator.animationDone();
}




void VehicleTrafficLight::runGoSequenceAnimation(Callback& doneCallback) {
    m_animator.startAnimation(ANIMATION_GO_TRAFFIC, &doneCallback, animate_goSequence_1);
}

void VehicleTrafficLight::animate_goSequence_1() {
    setYellow();
    m_animator.wait(VECHILE_GO_YELLOW_ms, animate_goSequence_2);
}

void VehicleTrafficLight::animate_goSequence_2() {
    setGreen();
    m_animator.animationDone();
}


