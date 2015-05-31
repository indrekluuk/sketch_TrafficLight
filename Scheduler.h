
#ifndef Scheduler_h
#define Scheduler_h

#include "Callback.h"
#include <Arduino.h>



class Scheduler {

private:
  static Scheduler* s_firstNode;
  Scheduler* m_nextNode = nullptr;
  
  unsigned long m_timer_ms = 0;
  unsigned long m_previousTime_ms = 0;
  bool isRunOnce = true;
  
  
public:

  Scheduler();
  virtual ~Scheduler();

  void runPeriodically(unsigned long time_ms);
  void runOnce(unsigned long time_ms);
  void clearTimer();
  static void run();


protected:
  virtual void call() = 0;


private:

  void link();
  void unlink();
  static Scheduler* getNodeBefore(Scheduler* node);
  
  bool isReady(const unsigned long& current_time_ms);

};



#endif


