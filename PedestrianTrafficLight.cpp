#include "PedestrianTrafficLight.h"
#include "Constants.h"


PedestrianTrafficLight::PedestrianTrafficLight(int redLedPin, int greenLedPin) :
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

void PedestrianTrafficLight::stop(Callback<> callback) {
    stopAnimation();
    runStopSequenceAnimation(callback);
}

void PedestrianTrafficLight::forceGo() {
    stopAnimation();
    setGreen();
}

void PedestrianTrafficLight::go(Callback<> callback) {
    forceGo();
    callback.call();
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



void PedestrianTrafficLight::runStopSequenceAnimation(Callback<> doneCallback) {
    m_animator.startAnimation(ANIMATION_STOP_PEDESTRIANS, doneCallback, animate_stopSequence_1);
}

void PedestrianTrafficLight::animate_stopSequence_1(Animator<PedestrianTrafficLight> *pAnimator) {
    pAnimator->getThis()->setGreenPulsing();
    pAnimator->wait(PEDESTRIAN_STOP_GREEN_BLINK_ms, animate_stopSequence_2);
}

void PedestrianTrafficLight::animate_stopSequence_2(Animator<PedestrianTrafficLight> *pAnimator) {
    pAnimator->getThis()->setRed();
    pAnimator->animationDone(pAnimator);
}


