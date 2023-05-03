#include "lab1/threadreaderstring.h"

#include <QObject>
#include <QThread>

#include "lab1/sharedstate.h"

ThreadReaderString::ThreadReaderString(SharedState* shared_state, int interval,
                                       QObject* parent)
    : ss_(shared_state), delay(interval), QThread{parent} {}

void ThreadReaderString::run() {
  forever {
    if (ss_->buf.empty()) {
      QThread::msleep(delay);
      continue;
    }

    auto inputValue = ss_->buf.front();
    ss_->buf.pop_front();
    emit updateGui(inputValue.first, inputValue.second);

    QThread::msleep(delay);
  }
}

void ThreadReaderString::setDelay(int del) { delay = del; }
