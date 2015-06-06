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
#include "Animator.h"





Animator::Animator() :
        m_animationNextCallback(*this, &Animator::initNextStep),
        m_animationDelayScheduler(&m_animationNextCallback),
        m_animationIdentifier(ANIMATION_STOPPED),
        m_animationStep(0),
        m_hasNextStep(false),
        m_animationDoneCallback(nullptr)
{

}



bool Animator::isAnimationRunning(uint8_t animationIdentifier) {
    return animationIdentifier == m_animationIdentifier;
}


void Animator::stopAnimation() {
    m_animationIdentifier = ANIMATION_STOPPED;
    m_animationStep = 0;
    m_animationDelayScheduler.clearTimer();
}



void Animator::initAnimation(uint8_t animationIdentifier, Callback* done) {
    m_animationIdentifier = animationIdentifier;
    m_animationStep = 0;
    m_animationDoneCallback = done;
    initNextStep();
}



void Animator::initNextStep() {
    m_animationStep++;
    m_hasNextStep = false;
    callNextStep();
    if (!m_hasNextStep) {
        animationDone();
    }
}



void Animator::nextWithDelay(uint32_t time_ms) {
    m_hasNextStep = true;
    m_animationDelayScheduler.runOnce(time_ms);
}



Callback& Animator::nextWhenDone() {
    m_hasNextStep = true;
    return m_animationNextCallback;
}



void Animator::animationDone() {
    stopAnimation();
    callDone();
}


void Animator::callDone() {
    if (m_animationDoneCallback != nullptr) {
        m_animationDoneCallback->call();
    }
}

