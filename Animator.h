#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"

template<class TAnimatedObj>
class Animator {

public:
    typedef void (TAnimatedObj::*CallbackMethod)(void);

    static const int ANIMATION_STOPPED = 0;

    TAnimatedObj& m_animatedObj;
    Scheduler m_animationScheduler;
    int m_animationIdentifier;
    CallbackTemplate<TAnimatedObj> m_nextStepCallback;
    Callback* m_animationDoneCallback;

public:

    Animator(TAnimatedObj &animatedObj);

    bool isAnimation(int animationIdentifier);

    void stopAnimation();



    void startAnimation(int animationIdentifier, CallbackMethod animationNext);

    void startAnimation(int animationIdentifier, Callback* done, CallbackMethod animationNext);

    void wait(unsigned long time_ms, CallbackMethod animationNext);

    Callback& waitForResponse(CallbackMethod animationNext);

    void animationDone();

private:
    void callDone();

};


template<class TAnimatedObj>
Animator<TAnimatedObj>::Animator(TAnimatedObj& animatedObj) :
        m_animatedObj(animatedObj),
        m_nextStepCallback(animatedObj),
        m_animationDoneCallback(nullptr),
        m_animationIdentifier(ANIMATION_STOPPED)
{
}


template<class TAnimatedObj>
bool Animator<TAnimatedObj>::isAnimation(int animationIdentifier) {
    return animationIdentifier == m_animationIdentifier;
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::stopAnimation() {
    m_animationIdentifier = ANIMATION_STOPPED;
    m_animationScheduler.clearTimer();
}


template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier,
                                            CallbackMethod animationNext) {
    startAnimation(animationIdentifier, nullptr, animationNext);
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::startAnimation(int animationIdentifier,
                                            Callback* done,
                                            CallbackMethod animationNext)
{
    m_animationIdentifier = animationIdentifier;
    m_animationDoneCallback = done;
    m_nextStepCallback(animationNext).call();
}

template<class TAnimatedObj>
void Animator<TAnimatedObj>::wait(unsigned long time_ms, CallbackMethod animationNext) {
    m_animationScheduler.runOnce(time_ms, &m_nextStepCallback(animationNext));
}


template<class TAnimatedObj>
Callback& Animator<TAnimatedObj>::waitForResponse(CallbackMethod animationNext) {
    return m_nextStepCallback(animationNext);
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


