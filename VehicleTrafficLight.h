#ifndef VehicleTrafficLight_h
#define VehicleTrafficLight_h


#include "TrafficLightBase.h"
#include "Light.h"

class VehicleTrafficLight : public TrafficLightBase {

    static const uint8_t ANIMATION_STOP_TRAFFIC = 1;
    static const uint8_t ANIMATION_GO_TRAFFIC = 2;


    Light m_redLight;
    Light m_yellowLight;
    Light m_greenLight;

    Animator<VehicleTrafficLight> m_animator;


public:

    VehicleTrafficLight(uint8_t redLedPin, uint8_t yellowLedPin, uint8_t greenLedPin);

    void off();// override;

    void forceStop();// override;

    void stop(Callback& callback);// override;

    void forceGo();// override;

    void go(Callback& callback);// override;

    void night();// override;

    void stopAnimation();// override;


private:

    void allLightsOff();

    void setRed();

    void setGreen();

    void setGreenPulsing();

    void setYellow();

    void setYellowPulsing();


    void runStopSequenceAnimation(Callback& doneCallback);
    void stopSequenceAnimationStep(uint8_t step);

    void runGoSequenceAnimation(Callback& doneCallback);
    void goSequenceAnimationStep(uint8_t step);


};


#endif


