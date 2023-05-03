#ifndef THREADREADERSTRING_H
#define THREADREADERSTRING_H

#include <QObject>
#include <QThread>

#include "lab1/sharedstate.h"

class ThreadReaderString : public QThread {
  Q_OBJECT

 public:
  explicit ThreadReaderString(SharedState* shared_state, int delay,
                              QObject* parent = nullptr);
  void run();
  void setDelay(int del);

 signals:
  void updateGui(const int thread, const int val);

 private:
  SharedState* ss_;
  int delay;
};

#endif  // THREADREADERSTRING_H
