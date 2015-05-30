
#ifndef PedestrianTrafficLight_h
#define PedestrianTrafficLight_h


#include "TrafficLightBase.h"
#include "Light.h"

class PedestrianTrafficLight : public TrafficLightBase {

  Light m_redLight;
  Light m_greenLight;
  
  
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
  
   
  void initStopSequence(void* callbackObj, Scheduler::CallbackFn* callbackFn);

  
};



#endif


