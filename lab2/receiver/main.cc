#include <QApplication>

#include "lab2/receiver/receiverwindow.h"

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  ReceiverWindow w;
  w.show();
  return a.exec();
}
