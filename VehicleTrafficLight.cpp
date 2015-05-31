#include "VehicleTrafficLight.h"
#include "Constants.h"


VehicleTrafficLight::VehicleTrafficLight(int redLedPin, int yellowLedPin, int greenLedPin) :
        m_animator(*this), m_redLight(redLedPin), m_yellowLight(yellowLedPin), m_greenLight(greenLedPin) {

}


void VehicleTrafficLight::switchState(Callback<> callback) {
    m_animator.stopAnimation();

    switch (m_currentState) {
        default:
        case STATE_OFF:
            allLightsOff();
            break;
        case STATE_STOP:
            if (callback.isInitialized()) {
                runStopSequenceAnimation(callback);
            } else {
                setRed();
            }
            break;
        case STATE_GO:
            setGreen();
            break;
        case STATE_NIGHT:
            setYellowPulsing();
            break;
    }
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


void VehicleTrafficLight::runStopSequenceAnimation(Callback<> doneCallback) {
    m_animator.startAnimation(ANIMATION_STOP_TRAFFIC, doneCallback, animate_stopSequence_1);
}

void VehicleTrafficLight::animate_stopSequence_1(Animator<VehicleTrafficLight> *pAnimator) {
    pAnimator->getThis()->setGreenPulsing();
    pAnimator->wait(VECHILE_STOP_GREEN_BLINK_ms, animate_stopSequence_2);
}

void VehicleTrafficLight::animate_stopSequence_2(Animator<VehicleTrafficLight> *pAnimator) {
    pAnimator->getThis()->setYellow();
    pAnimator->wait(VECHILE_STOP_YELLOW_ms, animate_stopSequence_3);
}

void VehicleTrafficLight::animate_stopSequence_3(Animator<VehicleTrafficLight> *pAnimator) {
    pAnimator->getThis()->setRed();
    pAnimator->getThis()->transitionEnded();
    pAnimator->animationDone(pAnimator);
}






