#ifndef Light_h
#define Light_h


#include "Scheduler.h"


class Light {

    int m_ledPin;
    bool m_isLedOn = false;
    Scheduler m_scheduler;
    CallbackTemplate<Light> m_togglePulseCallback;

public:
    Light(int pin);

    void on();

    void off();

    void pulse();

    void toggle();

private:

    void setLedOn();

    void setLedOff();

};


#endif


