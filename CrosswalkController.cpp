#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(int red1, int yellow1, int green1, int red2, int green2) :
        m_animator(*this),
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
    if (!m_animator.isAnimation(ANIMATION_BUTTON_PRESSED)) {
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
    m_animator.stopAnimation();
    m_vehicleTrafficLight.stopAnimation();
    m_pedestrianTrafficLight.stopAnimation();
}






void CrosswalkController::runPedestrianButtonCycleAnimation() {
    m_animator.startAnimation(ANIMATION_BUTTON_PRESSED, CrosswalkController::animate_buttonCycle_1);
}

void CrosswalkController::animate_buttonCycle_1() {
    m_pedestrianTrafficLight.forceStop();
    m_vehicleTrafficLight.stop(m_animator.waitForResponse(CrosswalkController::animate_buttonCycle_2));
}

void CrosswalkController::animate_buttonCycle_2() {
    m_animator.wait(PEDESTRIAN_GO_DELAY_ms, CrosswalkController::animate_buttonCycle_3);
}

void CrosswalkController::animate_buttonCycle_3() {
    m_pedestrianTrafficLight.go(m_animator.waitForResponse(CrosswalkController::animate_buttonCycle_4));
}

void CrosswalkController::animate_buttonCycle_4() {
    m_animator.wait(PEDESTRIAN_GO_GREEN_ms, CrosswalkController::animate_buttonCycle_5);
}

void CrosswalkController::animate_buttonCycle_5() {
    m_pedestrianTrafficLight.stop(m_animator.waitForResponse(CrosswalkController::animate_buttonCycle_6));
}

void CrosswalkController::animate_buttonCycle_6() {
    m_animator.wait(VECHILE_GO_DELAY_ms, CrosswalkController::animate_buttonCycle_7);
}

void CrosswalkController::animate_buttonCycle_7() {
    m_vehicleTrafficLight.go(m_animator.waitForResponse(CrosswalkController::animate_buttonCycle_8));
}

void CrosswalkController::animate_buttonCycle_8() {
    m_animator.animationDone();
}

 


