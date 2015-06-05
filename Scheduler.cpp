#include "Scheduler.h"


Scheduler *Scheduler::s_firstNode = nullptr;


Scheduler::Scheduler() :
        m_nextNode(nullptr),
        m_timer_ms(0),
        m_previousTime_ms(0),
        m_isRunOnce(true),
        m_callback(nullptr)
{
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

Scheduler *Scheduler::getNodeBefore(Scheduler *node) {
    if ((s_firstNode == nullptr) || (s_firstNode == node)) return nullptr;

    Scheduler* before = s_firstNode;
    while (before->m_nextNode != node) {
        before = before->m_nextNode;
    }
    return before;
}



void Scheduler::run() {
    uint32_t current_time_ms = millis();

    Scheduler *node = s_firstNode;
    while (node != nullptr) {
        node->checkTimer(current_time_ms);
        node = node->m_nextNode;
    }
}

void Scheduler::checkTimer(uint32_t current_time_ms) {
    if (isReady(current_time_ms)) {
        if (m_isRunOnce) {
            clearTimer();
        }
        call();
    }
}

bool Scheduler::isReady(const uint32_t &current_time_ms) {
    if (m_timer_ms == 0) return false;

    uint32_t elapsed_time_ms = current_time_ms - m_previousTime_ms;
    if (elapsed_time_ms > m_timer_ms) {
        m_previousTime_ms = m_previousTime_ms + m_timer_ms;
        return true;
    } else {
        return false;
    }
}



void Scheduler::runPeriodically(uint32_t time_ms, Callback* callback) {
    initCallback(callback);
    m_isRunOnce = false;
    startTimer(time_ms);
}

void Scheduler::runOnce(uint32_t time_ms, Callback* callback) {
    initCallback(callback);
    m_isRunOnce = true;
    startTimer(time_ms);
}



void Scheduler::initCallback(Callback* callback) {
    m_callback = callback;
}

void Scheduler::startTimer(uint32_t time_ms) {
    m_timer_ms = time_ms;
    m_previousTime_ms = millis();
}

void Scheduler::clearTimer() {
    m_timer_ms = 0;
}



void Scheduler::call() {
    if (m_callback != nullptr) {
        m_callback->call();
    }
}







