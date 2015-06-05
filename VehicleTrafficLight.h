#ifndef VehicleTrafficLight_h
#define VehicleTrafficLight_h


#include "TrafficLightBase.h"
#include "Light.h"

class VehicleTrafficLight : public TrafficLightBase {

    static const int ANIMATION_STOP_TRAFFIC = 1;
    static const int ANIMATION_GO_TRAFFIC = 2;


    Light m_redLight;
    Light m_yellowLight;
    Light m_greenLight;

    Animator<VehicleTrafficLight> m_animator;


public:

    VehicleTrafficLight(int redLedPin, int yellowLedPin, int greenLedPin);

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
    void animate_stopSequence_1();
    void animate_stopSequence_2();
    void animate_stopSequence_3();

    void runGoSequenceAnimation(Callback& doneCallback);
    void animate_goSequence_1();
    void animate_goSequence_2();


};


#endif


