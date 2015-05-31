
#ifndef CrosswalkController_h
#define CrosswalkController_h

#include "Animatable.h"
#include "VehicleTrafficLight.h"
#include "PedestrianTrafficLight.h"


class CrosswalkController : public Animatable {
  
  VehicleTrafficLight m_vehicleTrafficLight;
  PedestrianTrafficLight m_pedestrianTrafficLight;
  bool buttonAnimationInProgress = false;
  
  
public:
  CrosswalkController(int red1, int yellow1, int green1, int red2, int green2);

  void off();
  void on();
  void buttonPressed();
  void night();
  
  void stateChanged();
  
private:

  void initPedestrianButtonCycle();
  static void vehicleTrafficLightStopped(void* controller);

  
};



#endif


