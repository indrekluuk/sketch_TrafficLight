#ifndef Light_h
#define Light_h


#include "Scheduler.h"


class Light {

    uint8_t m_ledPin;
    bool m_isLedOn;
    Scheduler m_scheduler;
    CallbackTemplate<Light> m_togglePulseCallback;

public:
    Light(uint8_t pin);

    void on();

    void off();

    void pulse();

    void toggle();

private:

    void setLedOn();

    void setLedOff();

};


#endif


