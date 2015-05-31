
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

protected:
  
  void switchState(Callback<> callback) override;
  
  
private:
  void allLightsOff();
  void setRed();
  void setGreen();
  void setGreenPulsing();
  void setNight();
  
   
  void runStopSequenceAnimation(Callback<> doneCallback);

  
};



#endif


