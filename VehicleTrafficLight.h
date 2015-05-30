
#ifndef VehicleTrafficLight_h
#define VehicleTrafficLight_h


#include "TrafficLightBase.h"
#include "Light.h"

class VehicleTrafficLight : public TrafficLightBase {

  Light m_redLight;
  Light m_yellowLight;
  Light m_greenLight;
  

  
public:

  VehicleTrafficLight(int redLedPin, int yellowLedPin, int greenLedPin);

protected:
  void switchState(void* callbackObj, Scheduler::CallbackFn* callbackFn) override;
  
  
private:
  void allLightsOff();
  void setRed();
  void setGreen();
  void setGreenPulsing();
  void setYellow();
  void setYellowPulsing();


  void initStopSequence( void* callbackObj, Scheduler::CallbackFn* callbackFn);

 
  
};



#endif


