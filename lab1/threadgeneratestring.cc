#include "lab1/threadgeneratestring.h"

#include <Windows.h>

#include <QObject>
#include <QRandomGenerator>
#include <QThread>

#include "lab1/sharedstate.h"

ThreadGenerateString::ThreadGenerateString(SharedState* shared_state,
                                           int interval, int number,
                                           QObject* parent)
    : ss_(shared_state), delay_(interval), nThread_(number), QThread{parent} {}

void ThreadGenerateString::run() {
  forever {
    int newVal = QRandomGenerator::global()->generate() % 100;

    EnterCriticalSection(&ss_->criticalSection);
    while (ss_->buf.size() >= BUF_SIZE) {
      LeaveCriticalSection(&ss_->criticalSection);
      QThread::msleep(delay_);
      EnterCriticalSection(&ss_->criticalSection);
    }
    ss_->buf.push_back({nThread_, newVal});
    LeaveCriticalSection(&ss_->criticalSection);

    QThread::msleep(delay_);
  }
}

void ThreadGenerateString::setDelay(int del) { delay_ = del; }
