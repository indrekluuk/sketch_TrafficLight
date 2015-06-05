#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(uint8_t red1, uint8_t yellow1, uint8_t green1, uint8_t red2, uint8_t green2) :
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
    m_animator.startAnimation(ANIMATION_BUTTON_PRESSED, &CrosswalkController::pedestrianButtonCycleAnimationStep);
}

void CrosswalkController::pedestrianButtonCycleAnimationStep(uint8_t step) {
    switch (step) {
        case 1:
            m_pedestrianTrafficLight.forceStop();
            m_vehicleTrafficLight.stop(m_animator.nextWhenDone());
            break;
        case 2:
            m_animator.nextWithDelay(PEDESTRIAN_GO_DELAY_ms);
            break;
        case 3:
            m_pedestrianTrafficLight.go(m_animator.nextWhenDone());
            break;
        case 4:
            m_animator.nextWithDelay(PEDESTRIAN_GO_GREEN_ms);
            break;
        case 5:
            m_pedestrianTrafficLight.stop(m_animator.nextWhenDone());
            break;
        case 6:
            m_animator.nextWithDelay(VECHILE_GO_DELAY_ms);
            break;
        case 7:
            m_vehicleTrafficLight.go(m_animator.nextWhenDone());
            break;
        case 8:
            break;
    }
}

