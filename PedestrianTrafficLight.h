
#ifndef PedestrianTrafficLight_h
#define PedestrianTrafficLight_h


#include "TrafficLightBase.h"
#include "Light.h"

class PedestrianTrafficLight : public TrafficLightBase {

  static const int ANIMATION_STOP_PEDESTRIANS = 1;
  
  
  Light m_redLight;
  Light m_greenLight;
  
  Animator<PedestrianTrafficLight> m_animator;
  
  
public:

  PedestrianTrafficLight(int redLedPin, int greenLedPin);

protected:
  
  void switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) override;
  
  
private:
  void allLightsOff();
  void setRed();
  void setGreen();
  void setGreenPulsing();
  void setNight();
  
   
  void runStopSequenceAnimation(void* callbackObj, Scheduler::CallbackFn* callbackFn);

  
};



#endif


