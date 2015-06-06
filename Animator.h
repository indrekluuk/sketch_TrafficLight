/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Indrek Luuk (indrek.luuk@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef Animator_h
#define Animator_h


#include "Scheduler.h"

class Animator {

public:

    static const uint8_t ANIMATION_STOPPED = 0;

    MethodCallback<Animator> m_animationNextCallback;
    CallbackScheduler m_animationDelayScheduler;
    uint8_t m_animationIdentifier;
    uint8_t m_animationStep;
    bool m_hasNextStep;
    Callback* m_animationDoneCallback;

public:

    Animator();

    bool isAnimationRunning(uint8_t animationIdentifier);

    void stopAnimation();

    void nextWithDelay(uint32_t time_ms);
    Callback& nextWhenDone();

protected:

    void initAnimation(uint8_t animationIdentifier, Callback* done);
    virtual void callNextStep() = 0;

private:

    void initNextStep();
    void animationDone();
    void callDone();

};




template<class TAnimatedObj>
class MethodAnimator : public Animator {

public:
    typedef void (TAnimatedObj::*AnimationStepMethod)(uint8_t step);

private:
    TAnimatedObj& m_animatedObj;
    AnimationStepMethod m_animationStepMethod;


public:
    MethodAnimator(TAnimatedObj& animatedObj) :
            m_animatedObj(animatedObj), m_animationStepMethod(nullptr)
    {}

    void startAnimation(uint8_t animationIdentifier, AnimationStepMethod animationStepMethod) {
        startAnimation(animationIdentifier, nullptr, animationStepMethod);
    }

    void startAnimation(uint8_t animationIdentifier, Callback* done, AnimationStepMethod animationStepMethod) {
        m_animationStepMethod = animationStepMethod;
        initAnimation(animationIdentifier, done);
    }

    void callNextStep() { //override;
        if (m_animationStep != nullptr) {
            (m_animatedObj.*m_animationStepMethod)(m_animationStep);
        }
    }

};





#endif


