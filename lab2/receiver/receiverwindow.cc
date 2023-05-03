#include "lab2/receiver/receiverwindow.h"

#include <QObject>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "./ui_receiverwindow.h"

ReceiverWindow::ReceiverWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::ReceiverWindow),
      rmf_(new ReceiverMapFile(this)),
      timer_check_file_map_(new QTimer(this)),
      timer_receive_msg_(new QTimer(this)) {
  connect(timer_check_file_map_, &QTimer::timeout, this,
          &ReceiverWindow::onTryOpenMapFile);
  connect(timer_receive_msg_, &QTimer::timeout, rmf_,
          &ReceiverMapFile::checkMessage);
  connect(rmf_, &ReceiverMapFile::messageReceived, this,
          &ReceiverWindow::onMessageReceived);
  timer_check_file_map_->start(1000);
  ui_->setupUi(this);
  ui_->receiverStatusbar->showMessage("Trying to open map file...");
}

ReceiverWindow::~ReceiverWindow() {
  if (timer_receive_msg_->isActive()) {
    timer_receive_msg_->stop();
  }
  delete timer_receive_msg_;

  if (timer_check_file_map_->isActive()) {
    timer_check_file_map_->stop();
  }
  delete timer_check_file_map_;

  delete rmf_;
  delete ui_;
}

void ReceiverWindow::onTryOpenMapFile() {
  if (rmf_->tryOpenMapViewFile()) {
    timer_check_file_map_->stop();
    timer_receive_msg_->start(100);
    ui_->receiverStatusbar->showMessage("Map file opened successfully!");
  }
}

void ReceiverWindow::onMessageReceived(const QString message) {
  ui_->receiverListWidget->addItem(message);
  ui_->receiverListWidget->scrollToBottom();
}
