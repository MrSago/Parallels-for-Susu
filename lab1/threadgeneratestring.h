#ifndef THREADGENERATESTRING_H
#define THREADGENERATESTRING_H

#include <QObject>
#include <QThread>

#include "lab1/sharedstate.h"

class ThreadGenerateString : public QThread {
  Q_OBJECT

 public:
  explicit ThreadGenerateString(SharedState* shared_state, int interval,
                                int number, QObject* parent = nullptr);
  void run();
  void setDelay(int del);

 private:
  SharedState* ss_;
  int delay_;
  int nThread_;
};

#endif  // THREADGENERATESTRING_H
