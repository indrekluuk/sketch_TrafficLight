#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(int red1, int yellow1, int green1, int red2, int green2) :
  m_vehicleTrafficLight(red1, yellow1, green1), m_pedestrianTrafficLight(red2, green2)
{
}



void CrosswalkController::off() {
  stateChanged();
  m_vehicleTrafficLight.off();
  m_pedestrianTrafficLight.off();
}
  
void CrosswalkController::on() {
  stateChanged();
  m_vehicleTrafficLight.go();
  m_pedestrianTrafficLight.forceStop();
}
  
void CrosswalkController::buttonPressed() {
  if (!buttonAnimationInProgress) {
    stateChanged();
    initPedestrianButtonCycle();
  }  
}

void CrosswalkController::night() {
  stateChanged();
  m_vehicleTrafficLight.night();
  m_pedestrianTrafficLight.night();
}




void CrosswalkController::stateChanged() {
  stopCurrentAnimation();
  buttonAnimationInProgress = false;
}




void CrosswalkController::initPedestrianButtonCycle() {
  buttonAnimationInProgress = true;
  initAnimationDoneCallback(nullptr, nullptr);

  m_pedestrianTrafficLight.forceStop();  
  m_vehicleTrafficLight.stop(this, [](void* pThis) {
    animate(PEDESTRIAN_GO_DELAY_ms, pThis, [](void* pThis) {
      ((CrosswalkController*)pThis)->m_pedestrianTrafficLight.go();      
      animate(PEDESTRIAN_GO_GREEN_ms, pThis, [](void* pThis) {
        ((CrosswalkController*)pThis)->m_pedestrianTrafficLight.stop(pThis, [](void* pThis) {
          animate(VECHILE_GO_DELAY_ms, pThis, [](void* pThis) {
            ((CrosswalkController*)pThis)->m_vehicleTrafficLight.go();
            ((CrosswalkController*)pThis)->animationDone();
            ((CrosswalkController*)pThis)->buttonAnimationInProgress = false;
          });
        }); 
      });
    });
  });
}
    
 
 

