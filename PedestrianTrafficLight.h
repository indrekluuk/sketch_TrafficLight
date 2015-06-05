#ifndef PedestrianTrafficLight_h
#define PedestrianTrafficLight_h


#include "TrafficLightBase.h"
#include "Callback.h"
#include "Light.h"

class PedestrianTrafficLight : public TrafficLightBase {

    static const int ANIMATION_STOP_PEDESTRIANS = 1;


    Light m_redLight;
    Light m_greenLight;

    Animator<PedestrianTrafficLight> m_animator;


public:

    PedestrianTrafficLight(int redLedPin, int greenLedPin);

    void off() override;

    void forceStop() override;

    void stop(Callback& callback) override;

    void forceGo() override;

    void go(Callback& callback) override;

    void night() override;

    void stopAnimation() override;


private:

    void allLightsOff();

    void setRed();

    void setGreen();

    void setGreenPulsing();


    void runStopSequenceAnimation(Callback& doneCallback);
    void animate_stopSequence_1();
    void animate_stopSequence_2();


};


#endif


