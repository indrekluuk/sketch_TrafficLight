#ifndef CrosswalkController_h
#define CrosswalkController_h

#include "Animator.h"
#include "VehicleTrafficLight.h"
#include "PedestrianTrafficLight.h"


class CrosswalkController {

    static const uint8_t ANIMATION_BUTTON_PRESSED = 1;

    VehicleTrafficLight m_vehicleTrafficLight;
    PedestrianTrafficLight m_pedestrianTrafficLight;

    Animator<CrosswalkController> m_animator;


public:
    CrosswalkController(uint8_t red1, uint8_t yellow1, uint8_t green1, uint8_t red2, uint8_t green2);

    void off();

    void on();

    void buttonPressed();

    void night();

    void stopAnimation();

private:

    void runPedestrianButtonCycleAnimation();
    void pedestrianButtonCycleAnimationStep(uint8_t step);

};


#endif


