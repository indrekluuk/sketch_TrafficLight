
#ifndef Scheduler_h
#define Scheduler_h


class Scheduler {

public:
  typedef void(CallbackFn)(void*);
  
private:
  static Scheduler* s_firstNode;
  Scheduler* m_nextNode = nullptr;
  
  unsigned long m_timer_ms = 0;
  unsigned long m_previousTime_ms = 0;
  CallbackFn* m_callbackFn = nullptr;
  void* m_callbackObj;
  unsigned long isRunOnce = true;
  
  
public:

  Scheduler();
  virtual ~Scheduler();

  void initCallback(void* callbackObj, CallbackFn* callbackFn);
  void runPeriodically(unsigned long time_ms, void* callbackObj, CallbackFn* callbackFn);
  void runPeriodically(unsigned long time_ms);
  void runOnce(unsigned long time_ms, void* callbackObj, CallbackFn* callbackFn);
  void runOnce(unsigned long time_ms);
  void clearTimer();
  static void run();
  
  
  
private:

  void link();
  void unlink();
  static Scheduler* getNodeBefore(Scheduler* node);
  
  bool isReady(const unsigned long& current_time_ms);
  void callback();
  
};


#endif


