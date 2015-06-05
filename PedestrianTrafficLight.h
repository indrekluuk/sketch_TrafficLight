#ifndef PedestrianTrafficLight_h
#define PedestrianTrafficLight_h


#include "TrafficLightBase.h"
#include "Callback.h"
#include "Light.h"

class PedestrianTrafficLight : public TrafficLightBase {

    static const uint8_t ANIMATION_STOP_PEDESTRIANS = 1;


    Light m_redLight;
    Light m_greenLight;

    Animator<PedestrianTrafficLight> m_animator;


public:

    PedestrianTrafficLight(uint8_t redLedPin, uint8_t greenLedPin);

    void off();// override;

    void forceStop();// override;

    void stop(Callback& done);// override;

    void forceGo();// override;

    void go(Callback& done);// override;

    void night();// override;

    void stopAnimation();// override;


private:

    void allLightsOff();

    void setRed();

    void setGreen();

    void setGreenPulsing();


    void runStopSequenceAnimation(Callback& done);
    void stopSequenceAnimationStep(uint8_t step);


};


#endif


