#ifndef SENDERWINDOW_H
#define SENDERWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "lab2/sender/sendermapfile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SenderWindow;
}
QT_END_NAMESPACE

class SenderWindow : public QMainWindow {
  Q_OBJECT

 public:
  SenderWindow(QWidget* parent = nullptr);
  ~SenderWindow();

 private slots:
  void on_sendButton_clicked();

 private:
  Ui::SenderWindow* ui_;
  SenderMapFile* smf_;
};
#endif  // SENDERWINDOW_H
