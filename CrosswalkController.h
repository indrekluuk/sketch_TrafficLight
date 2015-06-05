#ifndef CrosswalkController_h
#define CrosswalkController_h

#include "Animator.h"
#include "VehicleTrafficLight.h"
#include "PedestrianTrafficLight.h"


class CrosswalkController {

    static const int ANIMATION_BUTTON_PRESSED = 1;

    VehicleTrafficLight m_vehicleTrafficLight;
    PedestrianTrafficLight m_pedestrianTrafficLight;

    Animator<CrosswalkController> m_animator;


public:
    CrosswalkController(int red1, int yellow1, int green1, int red2, int green2);

    void off();

    void on();

    void buttonPressed();

    void night();

    void stopAnimation();

private:


    void runPedestrianButtonCycleAnimation();
    void animate_buttonCycle_1();
    void animate_buttonCycle_2();
    void animate_buttonCycle_3();
    void animate_buttonCycle_4();
    void animate_buttonCycle_5();
    void animate_buttonCycle_6();
    void animate_buttonCycle_7();
    void animate_buttonCycle_8();

};


#endif


