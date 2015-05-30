#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(int red1, int yellow1, int green1, int red2, int green2) :
  m_vehicleTrafficLight(red1, yellow1, green1), m_pedestrianTrafficLight(red2, green2)
{
}



void CrosswalkController::off() {
  stopCurrentAnimation();
  m_vehicleTrafficLight.off();
  m_pedestrianTrafficLight.off();
}
  
void CrosswalkController::on() {
  stopCurrentAnimation();
  m_vehicleTrafficLight.go();
  m_pedestrianTrafficLight.forceStop();
}
  
void CrosswalkController::buttonPressed() {
  stopCurrentAnimation();
  initPedestrianButtonCycle();
}

void CrosswalkController::night() {
  stopCurrentAnimation();
  m_vehicleTrafficLight.night();
  m_pedestrianTrafficLight.night();
}





void CrosswalkController::initPedestrianButtonCycle() {
  initAnimationDoneCallback(nullptr, nullptr);

  m_pedestrianTrafficLight.forceStop();  
  m_vehicleTrafficLight.stop(this, [](void* pThis) {
    animate(PEDESTRIAN_GO_DELAY_ms, pThis, [](void* pThis) {
      ((CrosswalkController*)pThis)->m_pedestrianTrafficLight.go();      
      animate(PEDESTRIAN_GO_GREEN_ms, pThis, [](void* pThis) {
        ((CrosswalkController*)pThis)->m_pedestrianTrafficLight.stop(pThis, [](void* pThis) {
          animate(VECHILE_GO_DELAY_ms, pThis, [](void* pThis) {
            ((CrosswalkController*)pThis)->m_vehicleTrafficLight.go();
            ((CrosswalkController*)pThis)->callAnimationDone();
          });
        }); 
      });
    });
  });
}
    
 
 

