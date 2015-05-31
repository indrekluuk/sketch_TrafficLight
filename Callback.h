
#ifndef Callback_h
#define Callback_h


class Callback {

public:
  typedef void(CallbackFn)(void*);
  
private:

  void* m_callbackObj;
  CallbackFn* m_callbackFn;
  
public:

  Callback() :
    m_callbackObj(nullptr), m_callbackFn(nullptr)
  {}

  Callback(CallbackFn* callbackFn) :
          m_callbackObj(nullptr), m_callbackFn(callbackFn)
  {}

  Callback(void* callbackObj, CallbackFn* callbackFn) :
          m_callbackObj(callbackObj), m_callbackFn(callbackFn)
  {}

  bool isInitialized() {
    return m_callbackFn != nullptr;
  }

  void call() {
    if (isInitialized()) {
      m_callbackFn(m_callbackObj);
    }
  }

  
private:
  
};


#endif


