#ifndef Light_h
#define Light_h


#include "SchedulerTemplate.h"


class Light {

    int m_ledPin;
    bool m_isLedOn = false;
    SchedulerTemplate<Light> m_scheduler;

public:
    Light(int pin);

    void on();

    void off();

    void pulse();

    void toggle();

private:
    static void togglePulse(Light *light);

    void setLedOn();

    void setLedOff();

};


#endif


