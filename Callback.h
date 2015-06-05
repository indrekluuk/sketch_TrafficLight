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


