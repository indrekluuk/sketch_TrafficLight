#include "Scheduler.h"



Scheduler* Scheduler::s_firstNode = nullptr;


Scheduler::Scheduler() {
  link();
}

Scheduler::~Scheduler() {
  unlink();
}

void Scheduler::link() {
  if (s_firstNode == nullptr) {
    s_firstNode = this;
  } else {
    getNodeBefore(nullptr)->m_nextNode = this;
  }
}

void Scheduler::unlink() {
  if (s_firstNode == this) {
    s_firstNode = m_nextNode;
  } else {
    getNodeBefore(this)->m_nextNode = m_nextNode;
  }
}

Scheduler* Scheduler::getNodeBefore(Scheduler* node) {
  if ((s_firstNode == nullptr) || (s_firstNode == node)) return nullptr;

  Scheduler* before = s_firstNode;
  while (before->m_nextNode != node) {
    before = before->m_nextNode;
  }
  return before;
}





void Scheduler::runOnce(unsigned long time_ms) {
  m_timer_ms = time_ms;
  m_previousTime_ms = millis();
  isRunOnce = true;
}


void Scheduler::runPeriodically(unsigned long time_ms) {
  m_timer_ms = time_ms;
  m_previousTime_ms = millis();
  isRunOnce = false;
}


void Scheduler::clearTimer() {
  m_timer_ms = 0;
}

void Scheduler::run() {
  unsigned long current_time_ms = millis();

  Scheduler* node = s_firstNode;
  while (node != nullptr) {
    if (node->isReady(current_time_ms)) {
        if (node->isRunOnce) {
            node->clearTimer();
        }
        node->call();
    }
    node = node->m_nextNode;
  }
}



bool Scheduler::isReady(const unsigned long& current_time_ms) {
  if (m_timer_ms == 0) return false;

  unsigned long elapsed_time_ms = current_time_ms - m_previousTime_ms;
  if (elapsed_time_ms > m_timer_ms) {
    m_previousTime_ms = m_previousTime_ms + m_timer_ms;
    return true;
  } else {
    return false;
  }
}





