
#ifndef Light_h
#define Light_h


#include "Scheduler.h"


class Light {

  int m_ledPin;
  bool m_isLedOn = false;
  Scheduler scheduler;
  
public:
  Light(int pin);
  
  void on();
  void off();
  void pulse();
  void toggle();
  
private:
  static void togglePulse(void *light);
  void setLedOn();
  void setLedOff();
  
};



#endif


