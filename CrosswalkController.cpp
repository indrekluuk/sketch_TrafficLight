#include "CrosswalkController.h"
#include "Constants.h"


CrosswalkController::CrosswalkController(int red1, int yellow1, int green1, int red2, int green2) :
  m_animator(*this), m_vehicleTrafficLight(red1, yellow1, green1), m_pedestrianTrafficLight(red2, green2)
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
  if (!m_animator.isAnimation(ANIMATION_BUTTON_PRESSED)) {
    stateChanged();
    runPedestrianButtonCycleAnimation();
  }  
}

void CrosswalkController::night() {
  stateChanged();
  m_vehicleTrafficLight.night();
  m_pedestrianTrafficLight.night();
}




void CrosswalkController::stateChanged() {
  m_animator.stopAnimation();
}




void CrosswalkController::runPedestrianButtonCycleAnimation() {
  /*
  m_animator.startAnimation(ANIMATION_BUTTON_PRESSED, [](void* pAnimator) {
    Animator<CrosswalkController>::getThis(pAnimator)->m_pedestrianTrafficLight.forceStop();
    Animator<CrosswalkController>::getThis(pAnimator)->m_vehicleTrafficLight.stop(Callback(pAnimator, [](void* pAnimator) {
      Animator<CrosswalkController>::wait(pAnimator, PEDESTRIAN_GO_DELAY_ms, [](void* pAnimator) {
        Animator<CrosswalkController>::getThis(pAnimator)->m_pedestrianTrafficLight.go();      
        Animator<CrosswalkController>::wait(pAnimator, PEDESTRIAN_GO_GREEN_ms, [](void* pAnimator) {
          Animator<CrosswalkController>::getThis(pAnimator)->m_pedestrianTrafficLight.stop(Callback(pAnimator, [](void* pAnimator) {
            Animator<CrosswalkController>::wait(pAnimator, VECHILE_GO_DELAY_ms, [](void* pAnimator) {
              Animator<CrosswalkController>::getThis(pAnimator)->m_vehicleTrafficLight.go();
              Animator<CrosswalkController>::animationDone(pAnimator);
            });
          }));
        });
      });
    }));
  });
   */
}
    
 


