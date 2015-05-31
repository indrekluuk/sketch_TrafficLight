#include "CrosswalkController.h"
#include "VehicleTrafficLight.h"
#include "PedestrianTrafficLight.h"
#include "Light.h"
#include "Scheduler.h"



int redLed1 = 13;
int yellowLed1 = 12;
int greenLed1 = 11;

int redLed2 = 10;
int greenLed2 = 9;


CrosswalkController crosswalkController(redLed1, yellowLed1, greenLed1, redLed2, greenLed2);


int state = 0;
int previousState = 0;
boolean switchState = false;


void setup() {
  Serial.begin(9600);
  switchState = getSwitchState();
}


void loop() {

  if (getSwitchState() != switchState) {
    state++;
    switchState = !switchState;
  }

  if (state != previousState) {  
    Serial.println("Oleku muutus");
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

