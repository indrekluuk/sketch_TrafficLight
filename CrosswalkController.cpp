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

  m_animator.startAnimation(ANIMATION_BUTTON_PRESSED, [](Animator<CrosswalkController>* pAnimator) {
      pAnimator->getThis()->m_pedestrianTrafficLight.forceStop();
      pAnimator->getThis()->m_vehicleTrafficLight.stop(Callback<>(pAnimator, [](void* pObj) {
          Animator<CrosswalkController>* pAnimator = (Animator<CrosswalkController>*)pObj;
          pAnimator->wait(pAnimator, PEDESTRIAN_GO_DELAY_ms, [](Animator<CrosswalkController>* pAnimator) {
              pAnimator->getThis()->m_pedestrianTrafficLight.go();
              pAnimator->wait(pAnimator, PEDESTRIAN_GO_GREEN_ms, [](Animator<CrosswalkController>* pAnimator) {
                  pAnimator->getThis()->m_pedestrianTrafficLight.stop(Callback<>(pAnimator, [](void* pObj) {
                      Animator<CrosswalkController>* pAnimator = (Animator<CrosswalkController>*)pObj;
                      pAnimator->wait(pAnimator, VECHILE_GO_DELAY_ms, [](Animator<CrosswalkController>* pAnimator) {
                          pAnimator->getThis()->m_vehicleTrafficLight.go();
                          pAnimator->animationDone(pAnimator);
                      });
                  }));
              });
          });
      }));
  });

}
    
 


