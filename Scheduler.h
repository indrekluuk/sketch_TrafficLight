
#ifndef Scheduler_h
#define Scheduler_h


#include "Callback.h"


class Scheduler {

private:
  static Scheduler* s_firstNode;
  Scheduler* m_nextNode = nullptr;
  
  unsigned long m_timer_ms = 0;
  unsigned long m_previousTime_ms = 0;
  Callback m_callback;
  unsigned long isRunOnce = true;
  
  
public:

  Scheduler();
  virtual ~Scheduler();

  void initCallback(Callback callback);
  void runPeriodically(unsigned long time_ms, Callback callback);
  void runPeriodically(unsigned long time_ms);
  void runOnce(unsigned long time_ms, Callback callback);
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


