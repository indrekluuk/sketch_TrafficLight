#include "CrosswalkController.h"
#include "Scheduler.h"



uint8_t redLed1 = 13;
uint8_t yellowLed1 = 12;
uint8_t greenLed1 = 11;

uint8_t redLed2 = 10;
uint8_t greenLed2 = 9;


CrosswalkController crosswalkController(redLed1, yellowLed1, greenLed1, redLed2, greenLed2);


uint8_t state = 0;
uint8_t previousState = 0;
boolean switchState = false;


void setup() {
  //Serial.begin(9600);
  switchState = getSwitchState();
}


void loop() {

  if (getSwitchState() != switchState) {
    state++;
    switchState = !switchState;
  }

  if (state != previousState) {  
    //Serial.print("Oleku muutus ");
    //Serial.println(state);
    previousState = state;
    switch (state) {
      case 0:
        crosswalkController.off();
        break;
      case 1:
        crosswalkController.on();
        break;
      case 2:
        crosswalkController.buttonPressed();
        break;
      case 3:
        crosswalkController.buttonPressed();
        break;
      case 4:
        crosswalkController.night();
        break;
      default:
        state = 0;
        break;
    }
  }

  Scheduler::run();
}


bool getSwitchState() {
  return digitalRead(2);
}

