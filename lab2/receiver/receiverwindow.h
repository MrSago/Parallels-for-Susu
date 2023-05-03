#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "lab2/receiver/receivermapfile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ReceiverWindow;
}
QT_END_NAMESPACE

class ReceiverWindow : public QMainWindow {
  Q_OBJECT

 public:
  ReceiverWindow(QWidget* parent = nullptr);
  ~ReceiverWindow();

 public slots:
  void onTryOpenMapFile();
  void onMessageReceived(const QString message);

 private:
  Ui::ReceiverWindow* ui_;
  QTimer* timer_check_file_map_;
  QTimer* timer_receive_msg_;
  ReceiverMapFile* rmf_;
};
#endif  // RECEIVERWINDOW_H
