#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"

template<class TAnimatedObj>
class Animator {

public:
    typedef void (TAnimatedObj::*AnimationStepMethod)(uint8_t step);

    static const uint8_t ANIMATION_STOPPED = 0;

    MethodCallbackScheduler<Animator> m_animationScheduler;
    TAnimatedObj& m_animatedObj;
    uint8_t m_animationIdentifier;
    CallbackTemplate<Animator> m_otherAnimationDoneCallback;
    AnimationStepMethod m_animationStepMethod;
    uint8_t m_animationStep;
    bool m_hasNextStep;
    Callback* m_animationDoneCallback;

public:

    Animator(TAnimatedObj &animatedObj);

    bool isAnimation(uint8_t animationIdentifier);

    void stopAnimation();



    void startAnimation(uint8_t animationIdentifier, AnimationStepMethod animationStep);

    void startAnimation(uint8_t animationIdentifier, Callback* done, AnimationStepMethod animationStep);

    void nextWithDelay(uint32_t time_ms);

    Callback& nextWhenDone();

    void animationDone();

private:
    void nextStep();
    void callDone();

};


template<class TAnimatedObj>
Animator<TAnimatedObj>::Animator(TAnimatedObj& animatedObj) :
        m_animationScheduler(*this, &Animator::nextStep),
        m_animatedObj(animatedObj),
        m_animationIdentifier(ANIMATION_STOPPED),
        m_otherAnimationDoneCallback(*this, &Animator::nextStep),
        m_animationStepMethod(nullptr),
        m_animationStep(0),
        m_hasNextStep(false),
        m_animationDoneCallback(nullptr)
{

}


template<class TAnimatedObj>
bool Animator<TAnimatedObj>::isAnimation(uint8_t animationIdentifier) {
    return animationIdentifier == m_animationIdentifier;
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::stopAnimation() {
    m_animationIdentifier = ANIMATION_STOPPED;
    m_animationStep = 0;
    m_animationScheduler.clearTimer();
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(uint8_t animationIdentifier,
                                            AnimationStepMethod animationStep) {
    startAnimation(animationIdentifier, nullptr, animationStep);
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(uint8_t animationIdentifier,
                                            Callback* done,
                                            AnimationStepMethod animationStep)
{
    m_animationIdentifier = animationIdentifier;
    m_animationStepMethod = animationStep;
    m_animationStep = 0;
    m_animationDoneCallback = done;
    nextStep();
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::nextStep() {
    m_animationStep++;
    m_hasNextStep = false;
    if (m_animationStep != nullptr) {
        (m_animatedObj.*m_animationStepMethod)(m_animationStep);
    }
    if (!m_hasNextStep) {
        animationDone();
    }
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::nextWithDelay(uint32_t time_ms) {
    m_hasNextStep = true;
    m_animationScheduler.startTimerOnce(time_ms);
}


template<class TAnimatedObj>
Callback& Animator<TAnimatedObj>::nextWhenDone() {
    m_hasNextStep = true;
    return m_otherAnimationDoneCallback;
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::animationDone() {
    stopAnimation();
    callDone();
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::callDone() {
    if (m_animationDoneCallback != nullptr) {
        m_animationDoneCallback->call();
    }
}


#endif


