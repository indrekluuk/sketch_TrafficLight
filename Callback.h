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

#ifndef Callback_h
#define Callback_h

#include "global.h"


class Callback {
public:
    virtual void call() = 0;
};




template<class TObject>
class CallbackTemplate : public Callback {

public:
    typedef void (TObject::*CallbackMethod)(void);

private:
    TObject& m_object;
    CallbackMethod m_callbackMethod;

public:
    CallbackTemplate(TObject& object) :
            m_object(object), m_callbackMethod(nullptr) {};

    CallbackTemplate(TObject& object, CallbackMethod callbackMethod) :
            m_object(object), m_callbackMethod(callbackMethod) {};

    CallbackTemplate& operator()(CallbackMethod callbackMethod) {
        m_callbackMethod = callbackMethod;
        return *this;
    }

    void call() {
        if (m_callbackMethod != nullptr) {
            (m_object.*m_callbackMethod)();
        }
    };

};




#endif


