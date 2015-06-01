#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(int red1, int yellow1, int green1, int red2, int green2) :
        m_animator(*this), m_vehicleTrafficLight(red1, yellow1, green1), m_pedestrianTrafficLight(red2, green2) {
}


void CrosswalkController::off() {
    stateChanged();
    m_vehicleTrafficLight.off();
    m_pedestrianTrafficLight.off();
}

void CrosswalkController::on() {
    stateChanged();
    m_vehicleTrafficLight.forceGo();
    m_pedestrianTrafficLight.forceStop();
}

void CrosswalkController::buttonPressed() {
    if (!m_animator.isAnimation(ANIMATION_BUTTON_PRESSED)) {
        stateChanged();
        runPedestrianButtonCycleAnimation();
    }
}

void CrosswalkController::night() {
    stateChanged();
    m_vehicleTrafficLight.night();
    m_pedestrianTrafficLight.night();
}




void CrosswalkController::stateChanged() {
    m_animator.stopAnimation();
    m_vehicleTrafficLight.stopAnimation();
    m_pedestrianTrafficLight.stopAnimation();
}






void CrosswalkController::runPedestrianButtonCycleAnimation() {
    m_animator.startAnimation(ANIMATION_BUTTON_PRESSED, animate_buttonCycle_1);
}

void CrosswalkController::animate_buttonCycle_1(Animator<CrosswalkController> *pAnimator) {
    pAnimator->getThis()->m_pedestrianTrafficLight.forceStop();
    pAnimator->getThis()->m_vehicleTrafficLight.stop(pAnimator->waitForResponse(animate_buttonCycle_2));
}

void CrosswalkController::animate_buttonCycle_2(Animator<CrosswalkController> *pAnimator) {
    pAnimator->wait(PEDESTRIAN_GO_DELAY_ms, animate_buttonCycle_3);
}

void CrosswalkController::animate_buttonCycle_3(Animator<CrosswalkController> *pAnimator) {
    pAnimator->getThis()->m_pedestrianTrafficLight.go(pAnimator->waitForResponse(animate_buttonCycle_4));
}

void CrosswalkController::animate_buttonCycle_4(Animator<CrosswalkController> *pAnimator) {
    pAnimator->wait(PEDESTRIAN_GO_GREEN_ms, animate_buttonCycle_5);
}

void CrosswalkController::animate_buttonCycle_5(Animator<CrosswalkController> *pAnimator) {
    pAnimator->getThis()->m_pedestrianTrafficLight.stop(pAnimator->waitForResponse(animate_buttonCycle_6));
}

void CrosswalkController::animate_buttonCycle_6(Animator<CrosswalkController> *pAnimator) {
    pAnimator->wait(VECHILE_GO_DELAY_ms, animate_buttonCycle_7);
}

void CrosswalkController::animate_buttonCycle_7(Animator<CrosswalkController> *pAnimator) {
    pAnimator->getThis()->m_vehicleTrafficLight.go(pAnimator->waitForResponse(animate_buttonCycle_8));
}

void CrosswalkController::animate_buttonCycle_8(Animator<CrosswalkController> *pAnimator) {
    pAnimator->animationDone(pAnimator);
}

 


